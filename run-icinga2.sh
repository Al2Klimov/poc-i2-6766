#!/bin/bash

set -exo pipefail

perl -pi -e 'if (m~^//const NodeName\b~) { s~//~~; s/\blocalhost\b/$ENV{"NodeName"}/e }' /opt/icinga2/etc/icinga2/constants.conf

if [ "$NodeName" = master2 ]; then
	cat <<EOF >/opt/icinga2/etc/icinga2/zones.conf
object Endpoint "master1" {
	host = "172.17.0.1"
	port = "56651"
}

object Endpoint "master2" {
}

object Endpoint "sat1" {
	host = "172.17.0.1"
	port = "56653"
}

object Endpoint "sat2" {
	host = "172.17.0.1"
	port = "56654"
}

object Zone "master" {
	endpoints = [ "master1", "master2" ]
}

object Zone "sat" {
	endpoints = [ "sat1", "sat2" ]
	parent = "master"
}
EOF
else
	cat <<EOF >/opt/icinga2/etc/icinga2/zones.conf
object Endpoint "master1" {
}

object Endpoint "master2" {
}

object Endpoint "sat1" {
}

object Endpoint "sat2" {
}

object Zone "master" {
	endpoints = [ "master1", "master2" ]
}

object Zone "sat" {
	endpoints = [ "sat1", "sat2" ]
	parent = "master"
}
EOF
fi

if [ "$NodeName" = master1 ]; then
	mkdir -p /opt/icinga2/etc/icinga2/zones.d/sat

	cat <<EOF >/opt/icinga2/etc/icinga2/zones.d/sat/hosts.conf
object CheckCommand "silence" {
	command = [ "/bin/true" ]
}

object Host "invincible" {
	check_command = "silence"
}
EOF
fi

/opt/icinga2/sbin/icinga2 daemon -C
/opt/icinga2/sbin/icinga2 api setup

perl -pi -e 'if (/accept/) { s~//~~; s/false/true/ }' /opt/icinga2/etc/icinga2/features-available/api.conf

rm -vf /opt/icinga2/var/run/icinga2/icinga2.pid
exec /opt/icinga2/sbin/icinga2 daemon
