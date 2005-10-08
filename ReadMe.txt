#$GreyWolf's Stat Roller Help - Table of Contents

Help topics

What a stat roller does. HID_ABOUT

How to use the stat roller. HID_USE

How to choose a parse string. HID_PARSE

Auto accept HID_ACCEPT  
Send file on accept HID_RESPONSE

Contact information. HID_CONTACT



#$KWhat a stat roller does.

Many text-based MUDs give the player the chance to roll a number of stats when the first create their characters.  This rolling can provide a means to achieve stats that are more weighted in some areas than others.  It also leaves a bit up to chance.  Usually, the better stats you start out with, the better your new character will be able to cope with the harsh online world around him/her.

With enough patience, the player can usually achieve rolls that place their stats close to the maximum allowed stats.  That is where a stat roller comes in.  A stat roller is a tool that can be used to specify the minimum stats that a user is looking for.  It takes some of the frustration out of trying to get the perfect roll and allows the player to go do something else, while the roller does all the work.



#$KHow to use the stat roller.

GreyWolf's stat roller is designed to work with any text-based MUD that displays its roll information on a single line.  It uses a parse string to determine which lines fit the characteristics of a roll line, and parses out the actual roll values.  There are basically 6 steps involved in using this stat roller.

1.   Connect to the MUD server.  This is probably the most basic step.  Simply enter the address and port for the server of your choice and hit the connect button.

2.   Follow the prompts of your MUD until you get to the start of rolling.

3.   Choose a parse string based on the roll line. HID_PARSE 

4.   Select the stat values you want to roll and continue rolling by answering no to the first roll line.

5.   Sit back and let the roller roll for you until you receive a satisfactory roll.  When the roller stops, hit the accept or discard buttons depending on what you want to do.

6.   After you accept the roll, finish answering the final character creation questions until your character is created.

NOTE:  Steps 5 and 6 can now be automated by the use of auto accept HID_ACCEPT and send file on accept HID_RESPONSE



#$KHow to choose a parse string

Choosing a parse string is probably the most important part of successfully using this stat roller.  If you choose the wrong parse string, the roller will not be know when a roll line is encountered, or may parse the wrong stats.  

There are 2 things that must be considered when choosing which parse string to use.  You must consider where the numbers are in the roll line, and you must consider what other text is present in the roll line.  When choosing a parse string, you should choose one that exactly matches the display of the roll line with the numbers replaced with variables.  The variables are as follows...

%str  - used to parse out the strength number
%int - used to parse out the intelligence number
%wis - used to parse out the wisdom number
%dex - used to parse the dexterity number
%con - used to parse the constitution number
%oth - used to parse other numbers such as charisma

Here is an example of 2 different types of roll lines and the parse string that will parse it.  (These 2 examples seem fairly common, so they are included in the drop-down box by default.)

My favorite MUD is carrionfields, which has a roll line similar to this...
10str 15int 20wis 8dex 11con 18chr Do you wish to keep this roll (y/n)?

The correct parse string to use would look like this...
%strstr %intint %wiswis %dexdex %concon %othchr

NOTE: Anything in the roll line that goes beyond the parse string is discarded as garbage.

Here's another example... say your MUD has a roll line such as this...
Str: 8 Int: 20 Wis: 20 Dex: 10 Con: 15 Keep roll(y/n)?

The correct parse string would look like so...
Str: %str Int: %int Wis: %wis Dex: %dex Con: %con




#$KAuto accept

Auto accept is a new feature that I included to help automate the rolling process a bit more.  It should be used only if you will accept any rolls that match or exceed your desired roll settings.  If this option is selected, the roller will automatically accept any roll which matches the desired settings and continue with the character creation.



#$KSend file on accept

Send file on accept is a new feature which allows you to automate the final step of creating your character.  By using this in conjunction with Auto accept HID_ACCEPT you can let the roller take care of everything for you once the rolling process begins.  You should check to see what type of questions that are asked at the end of your character creation by creating a dummy character.  You can then put each response in a text file, with each response being placed on a separate line and select that as your response file in the roller.  

Here's a quick example...  Assume that your MUD's final questions look something like this...
Choose your hometown [G]aladon, Black[C]law, New [T]halos.
Choose an alignment (good/neutral/evil):

You could automatically answer these last two questions by creating a text file that looks like so...
T
Evil



#$KContact information

Please feel free to contact GreyWolf or WolfPak Dataworks to report any bugs, suggestions, or even criticisms.  (Criticisms should be given at your own risk, however.) :)

GreyWolf and WolfPak Dataworks can be contacted a couple of ways.  

You can e-mail WolfPak Dataworks at wolfpak@wolfpak.simplenet.com.

You can e-mail GreyWolf at greywolfwp@uswest.net.

You may also contact GreyWolf via ICQ at the UIN# 384887.

# HID_CONTENTS
$ Stat Roller help contents.
# HID_ABOUT
$ Stat rolling and how a stat roller helps automate the process
K About
# HID_USE
$ How to use GreyWolf's Stat Roller
K Use
# HID_PARSE
$ How to choose a parse string
K Parse strings
# HID_ACCEPT
$ How auto accept works
K Auto accept
# HID_RESPONSE
$ Automating final response
K File response
# HID_CONTACT
$ Contact information
K Contacting us.
