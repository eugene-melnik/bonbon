#!/usr/bin/expect -f

set s_hostname [lindex $argv 0]
set s_username [lindex $argv 1]
set s_password [lindex $argv 2]
set timeout 300

spawn ssh -X $s_username@$s_hostname

expect {
    "(yes/no)? " {
        send "yes\n"
        expect {
            "> " {}
            default {}
        }
    }
    "assword: " {
        send "$s_password\n"
        expect {
            "> " {}
            default {}
        }
    }
}

expect {
    "$ " {
        interact
    }
    "assword: " {
        send "$s_password\n"
        expect {
            "> " {}
            default {}
        }
    }
    default {
        exit
    }
}
