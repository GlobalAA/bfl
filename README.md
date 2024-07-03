## bfl interpreter
### bfl - simple brainfuck interpreter but for working with files
### The file extension must be .bf
<br/>

```
Input: -[------->+<]>-.-[->+++++<]>++.+++++++..+++.[--->+<]>-----.--[->++++<]>-.--------.+++.------.--------.
Output: Hello world 
```
<br/>


| Arguments   	| description                                                                                                                                            	| example                    	|
|-------------	|--------------------------------------------------------------------------------------------------------------------------------------------------------	|----------------------------	|
| target_dir  	| Allows you to translate all files in the directory from brainfuck to our human language.                                                               	| ./bfl -target_dir          	|
| target_file 	| Allows you to translate the specified file from brainfuck to our human language.                                                                       	| ./bfl -target_file=data.bf 	|
| s           	| A command with this argument will update the file. A command with this argument will update the file. Can also be used with target_dir and target_file 	| ./bfl -target_dir -s       	|
