
 >Visual Memory v0.9 Application  
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


    

# Visual Memory v0.9 * New Version Release *


A GUI, C++, Qt5 Visual Memory Analysis Program designed with Qt Creator.  

![alt text](https://github.com/RgbTrouw/VisualMemory/blob/root/Screenshot.png)  

This program is aimed at identifying images.  
  
A  set of pictures are stored as small 34x34 icons which serve as visual memory.  
  
This new version simplifies the pic identification process by runing an XoR alone.  
  
A color tolerance integer variable is used within the process.  
  
A QThread class is being employed (prevents app from freezing while the scan is done).  

  
 >XoR Truth Table  
 >  
 >1 xor 1 = 0  
 >0 xor 0 = 0  
 >  
 >1 xor 0 = 1  
 >0 xor 1 = 1  
...
