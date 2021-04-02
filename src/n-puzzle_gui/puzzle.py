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
        self.puzzleSize = puzzleSize
        self.pack(expand=Y, fill=BOTH)
        self.master.title('N-Puzzle GUI')
        self.isapp = True
        self.tileButtonList = [None] * puzzleSize ** 2
        self.tilePosArray = []
        self.posFactor = 1 / self.puzzleSize
        self.msgPanel = None
        self.seeDismissPanel = None
        self._create_widgets()

    def _create_widgets(self):
        if self.isapp:
            self.msgPanel = MsgPanel(self, ["Instruction:\n",
							"   - Click on any of the pieces next to the space and that\n",
                            "     piece will slide over the space.\n",
                            "   -  Continue this until the pieces are arranged in\n",
                            "      numerical order. Refer 4x4 result below.\n\n",
							"The end result in 4x4 puzzle:\n",
							" 1    2    3    4\n",
							"12  13  14   5\n",
							"11        15   6\n",
							"10   9    8    7"])
            self.seeDismissPanel = SeeDismissPanel(self)
        
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
        
        for i in range(self.puzzleSize):
            for j in range(self.puzzleSize):
                self.tilePosArray.append(None)
        for i in range(self.puzzleSize):
            for j in range(self.puzzleSize):
                num = self.puzzleTiles[i][j]
                self.tilePosArray[num] = (i, j)
                if (num == 0):
                    self.xypos['space'] = ( j * self.posFactor, i * self.posFactor)
                else:
                    self.xypos[num] = ( j * self.posFactor, i * self.posFactor)
                    b = ttk.Button(text=num, style='Puzzle.TButton')
                    self.tileButtonList[num] = b
                    b['command'] =lambda b=b: self.puzzle_switch(b)
                    b.place(in_=demoPanel, relx=self.xypos[num][0], rely=self.xypos[num][1],
                                                relwidth=self.posFactor, relheight=self.posFactor)
        
        # set button background to demoPanel background
        ttk.Style().configure('Puzzle.TButton', background=bgColor)
        
    def puzzle_switch(self, button):
        num = button['text']
        sx = self.xypos['space'][0]     # position of 'space'
        sy = self.xypos['space'][1]
        x = self.xypos[num][0]          # position of selected button
        y = self.xypos[num][1]
        
        # is the selected button next to the space?
        if(sy-.01 <= y <= sy+.01
            and sx - self.posFactor - .01 <= x <= sx + self.posFactor + .01
            or sx-.01 <= x <= sx+.01
            and sy - self.posFactor - .01 <= y <= sy + self.posFactor + .01):
            # swap button with space
            self.xypos['space'], self.xypos[num] = self.xypos[num], self.xypos['space']
            # re-position button
            button.place(relx=self.xypos[num][0], rely=self.xypos[num][1])
            tmp = self.tilePosArray[num]
            self.tilePosArray[num] = self.tilePosArray[0]
            self.tilePosArray[0] = tmp
    def getTileButtons(self):
        return (self.tileButtonList)
    def getEmptyTilePos(self):
        return (self.tilePosArray[0])
    def terminate_gui(self):
        print("EXIT................\n")
        # self.seeDismissPanel.winfo_toplevel().destroy()
        print("EXIT................\n")
        # self.seeDismissPanel.destroy()
        # self.msgPanel.winfo_toplevel().destroy()
        # self.msgPanel.destroy()
        return(self.seeDismissPanel)

if __name__ == '__main__':
	puzzleSize = 5
	puzzleTiles = [ [ 0,  1,  6,  2,  5],
					[ 7, 15,  3, 13,  4],
					[11,  8,  9, 14, 10],
					[12, 16, 17, 18, 19],
					[20, 21, 22, 23, 24]]
	puzzleDemo = PuzzleDemo(puzzleTiles, puzzleSize)
	puzzleDemo.mainloop()
