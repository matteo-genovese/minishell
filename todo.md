# TODO

## Tasks

- [x] parser token wrapper

## FIX

- [x] here doc 				Edofo
- [x] fix split sui pipe e sulle redirect	Starry
- [x] esecuzione builtin 			Federico
fixare attesa cat (?)
- [x] fixa echo				Matteo
- [x] redirect file descriptor esplicito
- [x] free if execve error correctly free command**
- [x] errore echo
```sh
echo "|"
# non printa
```
- [x] se scrivo "ciao | " returna un errore su ciao ma resta in attesa
- [x] devo fare exit 2 volte per uscire da minishell
- [x] se scrivo "ls > > file" dovrebbe dare: "bash: syntax error near unexpected token `>'" 
invece mi crea due file ( un file ">" vuoto e un file "file" con il risultato del ls)
- [x] errore redirect
```sh
cat < nofile(non esiste) > file2
# -> errore sbagliato
```
- [x] se scrivo "ls | | grep test" non ricevo errore
- [x] se scrivo "ls | exit" mi dice "double free or corruption (out)"
comportamento corretto:
"e3r3p1% bash
 edforte@e3r3p1:~/Desktop$ ls | exit
 edforte@e3r3p1:~/Desktop$ exit
 exit
 e3r3p1%"
- [x] se scrivo "echo $USER$HOME" mi stampa: "SER$HOME" invece bash "edforte/nfs/homes/edforte"
- [x] se scrivo "echo $NONEXIST" ottengo "ONEXIST" mentre dovrei ottenere linea vuota
- [x] "export " -> segfault
- [x] export -> error
```sh
"export """
# ritorna
declare -x LANGUAGE=en_US:en
declare -x USER=edforte
declare -x LC_TIME=en_US.UTF-8
declare -x XDG_SESSION_TYPE=x11
declare -x SHLVL=3
declare -x HOME=/nfs/homes/edforte
declare -x OLDPWD=/nfs/homes/edforte/Desktop/minishell
declare -x DESKTOP_SESSION=ubuntu
declare -x GTK_MODULES=gail:atk-bridge
declare -x XDG_SEAT_PATH=/org/freedesktop/DisplayManager/Seat0
declare -x LC_MONETARY=en_US.UTF-8
declare -x SYSTEMD_EXEC_PID=20572
declare -x DBUS_SESSION_BUS_ADDRESS=unix:path=/run/user/101040/bus
declare -x COLORTERM=truecolor
declare -x LIBVIRT_DEFAULT_URI=qemu:///system
declare -x GTK_IM_MODULE=ibus
declare -x LOGNAME=edforte
declare -x _=/nfs/homes/edforte/Desktop/minishell/./minishell
declare -x XDG_SESSION_CLASS=user
declare -x TERM=xterm-256color
declare -x GNOME_DESKTOP_SESSION_ID=this-is-deprecated
declare -x PATH=/nfs/homes/edforte/bin:/nfs/homes/edforte/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin:/nfs/homes/edforte/.dotnet/tools
declare -x SESSION_MANAGER=local/e3r3p1.42roma.it:@/tmp/.ICE-unix/20549,unix/e3r3p1.42roma.it:/tmp/.ICE-unix/20549
declare -x GDM_LANG=en
declare -x GNOME_TERMINAL_SCREEN=/org/gnome/Terminal/screen/4bfb1a7a_f0b1_4e0c_ade6_d8ff09c36d98
declare -x XDG_MENU_PREFIX=gnome-
declare -x XDG_SESSION_PATH=/org/freedesktop/DisplayManager/Session0
declare -x XDG_RUNTIME_DIR=/run/user/101040
declare -x LC_ADDRESS=en_US.UTF-8
declare -x DISPLAY=:0
declare -x LANG=en_US.UTF-8
declare -x XDG_CURRENT_DESKTOP=Unity
declare -x DOTNET_BUNDLE_EXTRACT_BASE_DIR=/nfs/homes/edforte/.cache/dotnet_bundle_extract
declare -x LC_TELEPHONE=en_US.UTF-8
declare -x XDG_SESSION_DESKTOP=ubuntu
declare -x XMODIFIERS=@im=ibus
declare -x GNOME_TERMINAL_SERVICE=:1.95
declare -x XAUTHORITY=/nfs/homes/edforte/.Xauthority
declare -x SSH_AUTH_SOCK=/run/user/101040/keyring/ssh
declare -x XDG_GREETER_DATA_DIR=/var/lib/lightdm-data/edforte
declare -x SSH_AGENT_LAUNCHER=gnome-keyring
declare -x KRB5CCNAME=FILE:/tmp/krb5cc_101040_jJeETs
declare -x SHELL=/bin/zsh
declare -x LC_NAME=en_US.UTF-8
declare -x QT_ACCESSIBILITY=1
declare -x GDMSESSION=ubuntu
declare -x DOCKER_HOST=unix:///run/user/101040/docker.sock
declare -x LC_MEASUREMENT=en_US.UTF-8
declare -x LC_IDENTIFICATION=en_US.UTF-8
declare -x GPG_AGENT_INFO=/run/user/101040/gnupg/S.gpg-agent:0:1
declare -x QT_IM_MODULE=ibus
declare -x PWD=/nfs/homes/edforte/Desktop/minishell
declare -x XDG_CONFIG_DIRS=/etc/xdg/xdg-ubuntu:/etc/xdg
declare -x XDG_DATA_DIRS=/usr/share/ubuntu:/usr/share/gnome:/nfs/homes/edforte/.local/share/flatpak/exports/share:/var/lib/flatpak/exports/share:/usr/local/share:/usr/share:/var/lib/snapd/desktop
declare -x LC_NUMERIC=en_US.UTF-8
declare -x LC_PAPER=en_US.UTF-8
declare -x VTE_VERSION=6800
declare -x CHROME_DESKTOP=code-url-handler.desktop
declare -x ORIGINAL_XDG_CURRENT_DESKTOP=ubuntu:GNOME
declare -x GDK_BACKEND=x11
declare -x TERM_PROGRAM=vscode
declare -x TERM_PROGRAM_VERSION=1.91.1
declare -x GIT_ASKPASS=/usr/share/code/resources/app/extensions/git/dist/askpass.sh
declare -x VSCODE_GIT_ASKPASS_NODE=/usr/share/code/code
declare -x VSCODE_GIT_ASKPASS_EXTRA_ARGS=
declare -x VSCODE_GIT_ASKPASS_MAIN=/usr/share/code/resources/app/extensions/git/dist/askpass-main.js
declare -x VSCODE_GIT_IPC_HANDLE=/run/user/101040/vscode-git-f5c0b39b3b.sock
declare -x VSCODE_INJECTION=1
declare -x ZDOTDIR=/nfs/homes/edforte
declare -x USER_ZDOTDIR=/nfs/homes/edforte
# return corretto
bash: export: `': not a valid identifier
```
- [x] se scrivo ```"echo ciao >>>>>> file"``` lo esegue senza problemi
- [x] errore sbagliato
```sh
;;;;;
# ritorna
minishell: ;;;;; command not found...
# return corretto
bash: syntax error near unexpected token `;;'

NON DOVENDO GESTIRE ';' STICAZZI FORTISSIMI, VA BENE QUESTO COME ERRORE
```
- [x] errore sbagliato pipe redirect
```sh
echo ciao | > file/.txt
# -> minishell: >: command not found
# return corretto
bash: file/.txt: No such file or directory
```

- [ ] null pointer errore sopra
```sh
Invalid read of size 1
==12872==    at 0x406691: ft_strncmp (ft_strncmp.c:19)
==12872==    by 0x405AC5: is_builtin (fork_processes.c:20)
==12872==    by 0x4048BB: invalid_command (execute_command.c:45)
==12872==    by 0x4060B9: command_error_handler (fork_processes.c:154)
==12872==    by 0x405E3E: child_process (fork_processes.c:91)
==12872==    by 0x404A31: execute_command (execute_command.c:84)
==12872==    by 0x401E8A: main (main.c:277)
==12872==  Address 0x0 is not stack'd, malloc'd or (recently) free'd
```
- [x] seg fault
```sh
echo dasdśd"asdas's""""da'sadsadsada"sadaasdasd'as
```

- [x] exit code sbagliato
```sh
echo <"./test_files/infile_big" | echo <"./test_files/infile"
# sbagliato 139 giusto 0
```

- [ ] exit code sbagliato
```sh
echo <"./minishell_tester/test_files/infile_big" | echo <"./minishell_tester/test_files/infile"
# sbagliato 139 giusto 0
```


# Test Suite Completo per Minishell

## Comandi Semplici e Variabili Globali

### Test Base
```bash
/bin/ls
/bin/cat /etc/hosts
/usr/bin/whoami
/bin/echo ciao
/bin/date
```

### Test Errori
```bash
/bin/comando_inesistente
/path/to/nonexistent/executable
/bin/ls /directory_inesistente
```

## Argomenti

### Test Base
```bash
/bin/ls -la
/bin/cat /etc/passwd /etc/hosts
/usr/bin/grep root /etc/passwd
/bin/echo ciao mondo
/bin/ls -l -a -h
/usr/bin/find . -name "*.c"
```

### Test Avanzati
```bash
/bin/ls -la /etc /var /home
/bin/grep -i -n "root" /etc/passwd
/usr/bin/find . -type f -name "*.c" -exec ls -la {} \;
/usr/bin/sort -r -n /tmp/numeri.txt
```

## Echo

### Test Base
```bash
echo
echo ciao
echo ciao mondo
echo "ciao mondo"
echo 'ciao mondo'
```

### Test Opzione -n
```bash
echo -n
echo -n ciao
echo -n "ciao mondo"
echo -n ciao mondo
```

### Test Multipli Argomenti
```bash
echo uno due tre
echo -n uno due tre
echo uno      due    tre
echo -n uno      due    tre
```

## Exit

### Test Base
```bash
exit
exit 0
exit 1
exit 42
```

### Test Errori
```bash
exit ciao
exit 42 43
exit -1
exit 9223372036854775808
```

## Virgolette Doppie

### Test Base
```bash
echo "ciao mondo"
echo "ciao    mondo"
echo "ciao mondo con \"virgolette\" all'interno"
echo "linea 1
linea 2"
```

### Test Avanzati
```bash
echo "cat lol.c | cat > lol.c"
echo "ls -la | grep .c > risultati.txt"
echo "   spazi   all'interno    delle virgolette   "
echo "simboli speciali: !@#$%^&*()_+-=[]{};:'\",.<>/?"
```

## Virgolette Singole

### Test Base
```bash
echo 'ciao mondo'
echo 'ciao    mondo'
echo 'ciao mondo con \'virgolette\' all\'interno'
echo 'linea 1
linea 2'
```

### Test Variabili d'Ambiente
```bash
echo '$USER'
echo '$HOME'
echo '$PATH'
echo 'testo con $USER in mezzo'
```

### Test Caratteri Speciali
```bash
echo '| > < ;'
echo '* ? [ ]'
echo '$(comando)'
echo '`comando`'
```

## Env

### Test Base
```bash
env
/usr/bin/env
```

## Export

### Test Base
```bash
export
export NUOVA_VAR=valore
export NUOVA_VAR="valore con spazi"
export VAR1=val1 VAR2=val2
```

### Test Sovrascrittura
```bash
export PATH=/nuovo/percorso:$PATH
export USER=nuovo_user
export HOME=/tmp
```

### Test Check
```bash
export TEST=valore
echo $TEST
env | grep TEST
```

## Unset

### Test Base
```bash
export TEST=valore
unset TEST
echo $TEST
```

### Test Multipli
```bash
export VAR1=val1 VAR2=val2 VAR3=val3
unset VAR1 VAR2
echo $VAR1 $VAR2 $VAR3
```

### Test Variabili Inesistenti
```bash
unset VARIABILE_INESISTENTE
unset
```

## CD

### Test Base
```bash
cd /
pwd
cd /tmp
pwd
cd ~
pwd
```

### Test Relativi
```bash
cd .
pwd
cd ..
pwd
cd ../..
pwd
```

### Test Errori
```bash
cd /directory_inesistente
cd /etc/hosts
cd ""
```

## PWD

### Test Base
```bash
pwd
cd /tmp && pwd
cd ~ && pwd
```

## Path Relativi

### Test Base
```bash
./minishell
../directory/file
../../directory/file
```

### Test Complessi
```bash
cd /tmp && ../../bin/ls
cd /usr && ../bin/ls -la ../etc/passwd
../../../../../../../bin/echo ciao
```

## Path d'Ambiente

### Test Base
```bash
ls
grep root /etc/passwd
find . -name "*.c"
```

### Test PATH
```bash
echo $PATH
export PATH=/bin:/usr/bin
ls
export PATH=
ls
which ls
```

### Test Priorità Percorsi
```bash
export PATH=/tmp:/bin
echo $PATH
ls
export PATH=/usr/local/bin:/usr/bin:/bin
echo $PATH
ls
```

## Redirezioni

### Test Input
```bash
cat < /etc/passwd
grep root < /etc/passwd
wc -l < /etc/passwd
```

### Test Output
```bash
echo ciao > output.txt
ls -la > risultato.txt
cat /etc/passwd > passwd_copy.txt
cat /etc/hosts >> hosts_append.txt
echo "nuova linea" >> hosts_append.txt
```

### Test Errori
```bash
cat < file_inesistente
cat < /etc/passwd > output.txt
ls -la > /directory_inesistente/file.txt
echo test > file1.txt > file2.txt > file3.txt
```

### Test Heredoc
```bash
cat << EOF
Questa è una linea.
Questa è un'altra linea.
$USER - Variabile che dovrebbe essere espansa.
'Virgolette singole'
"Virgolette doppie"
EOF

cat << DELIM
Test heredoc
con multiple
linee
DELIM
```

## Pipe

### Test Base
```bash
ls | grep .txt
cat /etc/passwd | grep root
echo ciao | cat
ls -la | grep .c | wc -l
```

### Test Avanzati
```bash
cat /etc/passwd | grep root | sort | uniq | wc -l
ls -la | grep "^d" | sort -r | head -3
echo ciao | cat | cat | cat
```

### Test Errori
```bash
ls file_inesistente | grep test
cat | grep | comando_inesistente
```

### Test Mix con Redirezioni
```bash
ls -la | grep .c > risultato.txt
cat < input.txt | grep parola | sort > output.txt
echo ciao | tee file.txt | cat
```

## Ctrl-C e History

### Test Ctrl-C
```bash
# Digita un comando lungo senza premere INVIO, poi premi Ctrl-C
ls -la /etc /var /usr /home /tmp
# Premi Ctrl-C e verifica che il buffer sia pulito

# Avvia un comando in esecuzione e interrompilo con Ctrl-C
cat
# Premi Ctrl-C mentre cat è in attesa di input
```

### Test History
```bash
# Esegui vari comandi
echo test1
echo test2
echo test3
# Usa i tasti Freccia Su e Freccia Giù per navigare nella history
```

### Test Comandi Errati
```bash
dsbksdgbksdghsd
asdfasdf
comando_inesistente con argomenti
```

### Test Pipe Multiple
```bash
cat | cat | ls
ls | cat | grep a | wc -l
```

### Test Comando Lungo
```bash
echo arg1 arg2 arg3 arg4 arg5 arg6 arg7 arg8 arg9 arg10 arg11 arg12 arg13 arg14 arg15 arg16 arg17 arg18 arg19 arg20 arg21 arg22 arg23 arg24 arg25 arg26 arg27 arg28 arg29 arg30
```

## Variabili d'Ambiente

### Test Base
```bash
echo $USER
echo $HOME
echo $PATH
echo "Il mio username è $USER"
```

### Test Interpolazione
```bash
echo "$USER"
echo '$USER'
echo "Home: $HOME, User: $USER"
echo "PATH=$PATH"
```

### Test Variabili Non Esistenti
```bash
echo $VARIABILE_INESISTENTE
echo "Test: $VARIABILE_INESISTENTE fine."
```

### Test Extra
```bash
echo ${USER}
echo $USER$HOME
echo "$USER$HOME"
echo "$USER/$HOME"
```

## Test Stress e Casi Speciali

### Test Combinazioni Complesse
```bash
export TEST="test value"; echo $TEST | grep test > result.txt && cat result.txt
cd /tmp && ls -la | grep "^d" | wc -l > count.txt; cat count.txt
(cd / && ls) | grep bin
```

### Test Sintassi Bash Avanzata
```bash
if [ -f /etc/passwd ]; then echo "esiste"; else echo "non esiste"; fi
for i in 1 2 3; do echo $i; done
echo $((5+5))
echo $(ls)
```

### Test Quote Miste
```bash
echo "Testo con 'virgolette singole' all'interno"
echo 'Testo con "virgolette doppie" all\'interno'
echo "Variabile: $USER e 'testo'"
```

### Test Caratteri Speciali
```bash
echo \$USER
echo "\\n\\t"
echo $?
echo !
```

## Test Combinati Finali

```bash
export TEST="valore test" && echo $TEST > output.txt && cat < output.txt | grep val | wc -l
cd /tmp && ls -la > ls_result.txt && cat ls_result.txt | grep "^d" > directories.txt && wc -l < directories.txt
```