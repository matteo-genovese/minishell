# Minishell

## Main

- tools init
- envp init (copy envp)

### Signals

- ignora QUIT
- handlder (INT, child)
- child (wait)
  - sigint -> \n
  - sigquit -> core dumped

### shell level

- $SHLVL = numero shell aperte
- la setta (get + add)

### Main loop

- get_ministr (gets prompt)
- readline
- g_signal (useless ?)
- add history
- parse
- setup tool
- check valid command (misto controllo parser)
  - special command (con pipe cambiano variabili ambientali)
  - set redirect
  - esecuzione switch

#### Esecuzione comando

##### Child

- pipe
- fork
- switch STDIN e STDOUT tra parent e child
- set command info
  - get paths split by ":"
    - preprocess se è un path
  - redirections
    - fd
    - fd = 42 => dopo c'è '|'
  - command setup
    - copia comando senza redirect & pipe
- error handler
  - invalid command
  - errori fd
- reset SIGQUIT -> default
- execve

##### Parent

- ignora SIGINT
- se last command -> wait
  - check appesi
  - exit in base a sig oppure exitcode
- last exit
- 