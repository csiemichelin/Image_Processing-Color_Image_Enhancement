# Image_Processing-Color_Image_Enhancement
## 目錄
 - [Data_handed_in](#Data_handed_in)
 - [Technical_description](#Technical_description)
 - [Experimental_results](#Experimental_results)
## Data_handed_in  
**1. Color_Image_Enhancement 資料夾**  
&emsp;Color_Image_Enhancement.cpp    
&emsp;Color_Image_Enhancement.exe    
&emsp;aloe.jpg   
&emsp;church.jpg   
&emsp;house.jpg   
&emsp;kitchen.jpg         
## Technical_description  
**1. RGB**
&emsp;(1) 目的 : 把圖片中的 RGB 抽出來，然後分別對 B、G、R 做histogram equalization，然後再把結果結合起來。  
**2. HSI**
&emsp;(1) 目的 : 將RGB轉成HSI後，對I做優化，然後轉回RGB以輸出。   
&emsp;(2) 公式 :     
&emsp;&emsp;I. RGB to HSI:    
&emsp;&emsp;&emsp;<img src="https://github.com/csiemichelin/Image_Processing-Color_Image_Enhancement/blob/main/tech_image/1.png" width="200" height="200">      
&emsp;&emsp;&emsp;RGB在[0,1]區間    
&emsp;&emsp;II. HSI to RGB:   
&emsp;&emsp;&emsp;(一) RG sector(0 <= H < 120)     
&emsp;&emsp;&emsp;<img src="https://github.com/csiemichelin/Image_Processing-Color_Image_Enhancement/blob/main/tech_image/2.png" width="150" height="120">   
&emsp;&emsp;&emsp;(二) RG sector(120 <= H < 240)   
&emsp;&emsp;&emsp;<img src="https://github.com/csiemichelin/Image_Processing-Color_Image_Enhancement/blob/main/tech_image/3.png" width="150" height="130">   
&emsp;&emsp;&emsp;(三) RG sector(240 <= H < 360)   
&emsp;&emsp;&emsp;<img src="https://github.com/csiemichelin/Image_Processing-Color_Image_Enhancement/blob/main/tech_image/4.png" width="140" height="120">    
**3. L*a*b**   
&emsp;(1) 目的 : 將RGB轉成L*a*b時，一併優化圖像，然後轉回RGB以輸出RGB轉為XYZ，此處以LAB代表XYZ。   
&emsp;(2) 公式 :   
&emsp;&emsp;I. RGB to L*a*b:   
&emsp;&emsp;&emsp;<img src="https://github.com/csiemichelin/Image_Processing-Color_Image_Enhancement/blob/main/tech_image/5.png" width="270" height="90">   
&emsp;&emsp;&emsp;<img src="https://github.com/csiemichelin/Image_Processing-Color_Image_Enhancement/blob/main/tech_image/6.png" width="330" height="90">   
&emsp;&emsp;&emsp;<img src="https://github.com/csiemichelin/Image_Processing-Color_Image_Enhancement/blob/main/tech_image/7.png" width="200" height="100">&emsp;&emsp;&emsp;<img src="https://github.com/csiemichelin/Image_Processing-Color_Image_Enhancement/blob/main/tech_image/8.png" width="200" height="90">   
&emsp;&emsp;&emsp;RGB在[0,1]區間    
&emsp;&emsp;II. L*a*b to RGB:  
&emsp;&emsp;&emsp;<img src="https://github.com/csiemichelin/Image_Processing-Color_Image_Enhancement/blob/main/tech_image/9.png" width="450" height="350">   
## Experimental_results
&emsp;(1) 前置作業 :      
&emsp;&emsp;(一) 作業系統 : Windows 10 家用版     
&emsp;&emsp;(二) Visual studio 版本 : Visual Studio 2019     
&emsp;&emsp;(三) OpenCV 版本 : OpenCV 4.5.3     
&emsp;&emsp;(四) 環境架設 :        
&emsp;&emsp;&emsp;https://forum.gamer.com.tw/C.php?bsn=60292&snA=6494   
&emsp;(2) Color_Image_Enhancement(左至右依序為:原圖,RGB,HIS,L*a*b*)   
&emsp;&emsp;(一) aloe.jpg       
&emsp;&emsp;(二) church.jpg     
&emsp;&emsp;(三) house.jpg        
&emsp;&emsp;(四) kitchen.jpg     
