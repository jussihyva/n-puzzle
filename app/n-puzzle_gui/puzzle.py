# File: puzzle.py
# References:
#    'Python and Tkinter Programming' by John Grayson, p90
#    http://www.tcl.tk/man/tcl8.5/TkCmd/place.htm
#    http://www.tcl.tk/man/tcl8.5/TkCmd/colors.htm

from tkinter import *
from tkinter import ttk
from demopanels import MsgPanel, SeeDismissPanel

class PuzzleDemo(Frame):
    
    def __init__(self, puzzleTiles, puzzleSize):
        Frame.__init__(self, name='puzzledemo')
        self.puzzleTiles = puzzleTiles
        self.pack(expand=Y, fill=BOTH)
        self.master.title('15 Puzzle Demo')
        self.isapp = True
        self.tileButtonList = [None] * puzzleSize ** 2
        self._create_widgets()
        
    def _create_widgets(self):
        if self.isapp:
            MsgPanel(self, ["A 15-puzzle appears below as a collection of buttons.  ",
                            "Click on any of the pieces next to the space and that ",
                            "piece will slide over the space.\n\n",
                            "Continue this until the pieces are arranged in numerical ",
                            "order from upper-left to lower-right."])
            
            SeeDismissPanel(self)
        
        self._create_demo_panel()
        
    def _create_demo_panel(self):
        bgColor = 'gray80'  # colour for panel background and empty space
        
        # if width and height are not specifically set buttons are positioned
        # in a 0 size window and do not show up
        demoPanel = Frame(self, borderwidth=2, relief=SUNKEN, background=bgColor,
                          width=520, height=520)
        demoPanel.pack(side=TOP, pady=1, padx=1)
        
        # buttons are placed relative to the top, left corner of demoPanel
        # with relations expressed as a value between 0.0 and 1.0
        # top, left corner = (x,y) = (0,0)
        # bottom, right corner = (x,y) = (1,1)
        self.xypos = {}
        
        for i in range(5):
            for j in range(5):
                num = self.puzzleTiles[i][j]
                if (num == 0):
                    self.xypos['space'] = ( j * .20, i * .20)
                else:
                    self.xypos[num] = ( j * .20, i * .20)
                    b = ttk.Button(text=num, style='Puzzle.TButton')
                    self.tileButtonList[num] = b
                    b['command'] =lambda b=b: self.puzzle_switch(b)
                    b.place(in_=demoPanel, relx=self.xypos[num][0], rely=self.xypos[num][1],
                                                relwidth=.20, relheight=.20)
        
        # set button background to demoPanel background
        ttk.Style().configure('Puzzle.TButton', background=bgColor)
        
    def puzzle_switch(self, button):
        num = button['text']
        sx = self.xypos['space'][0]     # position of 'space'
        sy = self.xypos['space'][1]
        x = self.xypos[num][0]          # position of selected button
        y = self.xypos[num][1]
        
        # is the selected button next to the space?
        if(    sy-.01 <= y <= sy+.01 and sx-.26 <= x <= sx+.26
            or sx-.01 <= x <= sx+.01 and sy-.26 <= y <= sy+.26):
            
            # swap button with space
            self.xypos['space'], self.xypos[num] = self.xypos[num], self.xypos['space']
            
            # re-position button
            button.place(relx=self.xypos[num][0], rely=self.xypos[num][1])
    def getTileButtons(self):
        return (self.tileButtonList)

if __name__ == '__main__':
	puzzleSize = 5
	puzzleTiles = [ [ 0,  1,  6,  2,  5],
					[ 7, 15,  3, 13,  4],
					[11,  8,  9, 14, 10],
					[12, 16, 17, 18, 19],
					[20, 21, 22, 23, 24]]
	puzzleDemo = PuzzleDemo(puzzleTiles, puzzleSize)
	puzzleDemo.mainloop()
