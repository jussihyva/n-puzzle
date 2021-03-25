# File: puzzle.py
# References:
#    'Python and Tkinter Programming' by John Grayson, p90
#    http://www.tcl.tk/man/tcl8.5/TkCmd/place.htm
#    http://www.tcl.tk/man/tcl8.5/TkCmd/colors.htm

from tkinter import *
from tkinter import ttk
from demopanels import MsgPanel, SeeDismissPanel

class PuzzleDemo(Frame):
    
    def __init__(self, isapp=True, name='puzzledemo'):
        Frame.__init__(self, name=name)
        self.pack(expand=Y, fill=BOTH)
        self.master.title('15 Puzzle Demo')
        self.isapp = isapp
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
                          width=120, height=120)
        demoPanel.pack(side=TOP, pady=1, padx=1)
        
        # buttons are placed relative to the top, left corner of demoPanel
        # with relations expressed as a value between 0.0 and 1.0
        # top, left corner = (x,y) = (0,0)
        # bottom, right corner = (x,y) = (1,1)
        self.xypos = {}
        self.xypos['space'] = (.75, .75)
        order = [3, 1, 6, 2, 5, 7, 15, 13, 4, 11, 8, 9, 14, 10, 12]
        
        for i in range(15):
            num = order[i]
            self.xypos[num] = ( i%4 * .25, i//4 * .25)
            b = ttk.Button(text=num, style='Puzzle.TButton')
            b['command'] =lambda b=b: self._puzzle_switch(b)
            b.place(in_=demoPanel, relx=self.xypos[num][0], rely=self.xypos[num][1],
                    relwidth=.25, relheight=.25)
        
        # set button background to demoPanel background
        ttk.Style().configure('Puzzle.TButton', background=bgColor)
        
    def _puzzle_switch(self, button):
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
        
if __name__ == '__main__':
    PuzzleDemo().mainloop()
