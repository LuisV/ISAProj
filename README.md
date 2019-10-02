# ChickenScratch :chicken: :balloon:
16 bit code: 4 bit opCode, 4 bit addressing, Parameters: 3 possible

![picture alt](https://www.thespruce.com/thmb/REHCMZpetkTU1B4bGra-xkbRrTg=/2599x1922/filters:no_upscale():max_bytes(150000):strip_icc()/WELP_CHICK-57f187a63df78c690ffdee17.jpg "The Chicken")
 
### Registers

R0 - R7

## Instructions with opcodes

disp: 0000 - “Display the contents of an address” 

input: 0001 - “Takes input from keyboard and stores into address” 

move: 0010 - “Takes a register value and copies it to a register” 

add: 0011 - “Adds 2 data locations and stores into a data location”

subt: 0100 - “Subtracts 2 data locations and stores into a data location”

mult: 0101- “Multiplies two data locations and store into a data location”

div: 0110 - “Divides two data locations and store into a data location”

mod: 0111 - “Mods two data location and stores into a data locations”

jump: 1000 - "Allows for user to go to a desired line"

cond: 1001 - "Compares two entered values with each other or one value to zero, if true then it skips the next line"

           Conditions
            
           condition: 1-> if num1 is > num2
           
           condition: 2-> if num1 < num2
            
           condition: 3-> if num1 = num2
            
           condition: 4-> if num1 == 0 

put: 1010 - “Places integer value into register” ** this function can take a number up to 6 bits i.e. 0 through 63”

var: 1011 - "Creates a variable"

array: 1100 - "Creats an array"

## Using the Program

Declaration of variables must be defined at start of program

disp   (variable to display)

input  (variable to input to)

move    (variable to move)   (destination)

add     (condition)   (variable1)   (variable2)

subt    (variable1)   (variable2) 

mult    (variable1)   (variable2) 

div    (variable1)   (variable2)

mod    (variable to save to)  (variable1)   (variable2) 

jump   (line number in a variable)

cond   (1 or 2 or 3) (num1) (num2)

cond   (4) (num)

put    (variable)  (dec value)

var    (variable name) (dec value) 

array  (varable name) (array length)
