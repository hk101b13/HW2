# HW2
(1) how to setup and run your program
choice(): 顯示選項
up_fun()  down_fun() ： 控制箭頭上下
Output()：產生三角波
select_freq() ：按下後比對箭頭座標 輸出相應頻率

button up: A0
button down: A1
button select: A4

D13--low-pass fliter(50nF,12kohm)--A3--picoscope


(2) what are the results
triangle wave with S=6
FFT: the freq of 200Hz will rise if we select 200Hz
     the amplitude will decrease if we select freq=300Hz
