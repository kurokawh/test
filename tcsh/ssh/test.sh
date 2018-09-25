#!/bin/tcsh
#
# NOTE: > source test.sh

### tcshrc for ssh-agent ===> ###
setenv SSH_ENV "$HOME/.ssh/environment"
setenv SSHAGENT `which ssh-agent`

if ( -f "${SSH_ENV}" ) then
    #echo "env file found: ${SSH_ENV}"
    source "${SSH_ENV}"
    #echo "SSH_AGENT_PID: ${SSH_AGENT_PID}"
    #echo "SSH_AUTH_SOCK: ${SSH_AUTH_SOCK}"
    #ps ${SSH_AGENT_PID} doesn't work under cywgin
    ps -ef | grep ${SSH_AGENT_PID} | grep ssh-agent > /dev/null
    if ( $status == 1 ) then
        #echo "no agent found ${SSH_AGENT_PID}"
        goto call_start_agent
    endif
    #echo "agent found! ${SSH_AGENT_PID}"
    ssh-add -l | grep -i "${HOME}/.ssh/id_" > /dev/null
    if ( $status == 1 ) then
        #echo "no key added."
        goto call_ssh_add
    endif
else
    #echo "no environment file."
    goto call_start_agent
endif
goto exit_ssh

# Source SSH settings, if applicable
call_start_agent:
    echo -n "Initialising new SSH agent... "
    ${SSHAGENT} -c | sed 's/^echo/#echo/' > "${SSH_ENV}"
    echo succeeded
    chmod 700 "${SSH_ENV}"
    source "${SSH_ENV}"
    #echo "after start SSH_AGENT_PID: ${SSH_AGENT_PID}"
    #echo "after start SSH_AUTH_SOCK: ${SSH_AUTH_SOCK}"

	if ( -e "$HOME/.local_host.csh" ) then
		# run only once.
		echo -n "load platform local script (.local_host.csh): "
		source "$HOME/.local_host.csh"
		echo "DONE"
	endif

call_ssh_add:
    ssh-add ~/.ssh/{id_rsa,id_dsa,id_ed25519,identity} ~/.ssh/*/{id_rsa,id_dsa,id_ed25519,identity}

exit_ssh:
### <=== ssh-agent ###
