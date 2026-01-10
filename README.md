
 >Visual Memory v0.8d Application  
 Copyright (C) 2025-2026  Radu G. Balaban G.  

 >This program is free software: you can redistribute it and/or modify  
 it under the terms of the GNU General Public License as published by  
 the Free Software Foundation, either version 3 of the License, or  
 (at your option) any later version.  

 >This program is distributed in the hope that it will be useful,  
 but WITHOUT ANY WARRANTY; without even the implied warranty of  
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  
 GNU General Public License for more details.  

 >You should have received a copy of the GNU General Public License  
 along with this program. If not, see <https://www.gnu.org/licenses/>.


    

# Visual Memory v0.8d


A GUI, C++, Qt5 Visual Memory Analysis Program designed with Qt Creator.

This program is aimed at identifying images. 
A  set of pictures are stored as small 34x34 icons which serve as visual memory.

The program is under development, but it does display some partial results. 

  * To initialise memory: Edit-> Memory-> Convert to Shapes;  

Some cross check functions are made between a subject picture and memory after a high contrast conversion.
  
 For now, the algorighm only works with black background icons and does not distinguish colors. (serving for a simple, heuristic shape comparison)  
  
An xor function with score weight serves as the starting point for the image identification procedure, where 0 is the best match score.  

Ie.
1. Subject file is loaded.
2. Subject file is converted to a low res, 34x34 Image. (This simplifies the processing requirements)  
3. Subject file is converted to a high contrast black & white picture. (black = black; !black = white;)  
4. Xor function is run against the memory icons. (Also at high contrast conversion)
5. Closest matches are displayed, ordered by their scores. (*note that the code will sort and display all memory icons and not only the first few best matches)    


More functions like identify containing objects    based on same color neighbor pixel syntax, plus overall color weight scores may be added next.



 >XoR Truth Table  
 >  
 >1 xor 1 = 0  
 >0 xor 0 = 0  
 >  
 >1 xor 0 = 1  
 >0 xor 1 = 1  

...
