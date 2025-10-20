
 >Visual Memory v0.8d Application  
 Copyright (C) 2025  Radu G. Balaban G.  

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


A GUI, C++ Visual Memory Analysis Program in Qt Creator.

This program is aimed at identifying images. 
A  set of pictures are stored as small 34x34 icons which serve as visual memory.

The gui is under development, but it does display some partial results. 

  * To initialise memory: Edit-> Memory-> Convert to Shapes;  

Some cross check functions are made between a subject picture and memory after a high contrast conversion.

(a simple xor function with score weight serves as the starting point for the image identification procedure)

Ie.
1. Subject file is loaded.
2. Subject file is converted to a low res, 34x34 Image. (This simplifies the processing procedure)
3. Subject file is converted to a high contrast black & white picture. (Heuristic shape comparison)
4. Xor function is run against the memory icons. (Also at high contrast conversion)
5. Closest matches are displayed, ordered by their scores.  


More functions like identify objects (shapes) based on same color neighbor pixel syntax, plus overall color weights may be added next.

 >XoR Truth Table  
 >  
 >1 xor 1 = 0  
 >0 xor 0 = 0  
 >  
 >1 xor 0 = 1  
 >0 xor 1 = 1  

...
