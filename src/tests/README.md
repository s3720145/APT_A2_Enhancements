A single test will consist of the following:
.in file:       this is to load the game state
.inputs file:   this will consist of player commands
.out file:      this should represent the expected output after the player commands have run
                and have been saved

For our implementation we actually used a specific command to put the chosen tiles 
into broken tiles. This command should only be employed in the event all rows are unavailable.
It's similar to a normal command like this 'turn factory tile storage' however instead of an 
integer representing a storage row it will be the character 'b' as in 'turn factory tile b'.

Centre factory is also represented as 0 and a normal command will look like 'turn 0 R 2'.