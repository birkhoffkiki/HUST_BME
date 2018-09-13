"""
UFace 主文件，显示图形界面以及计算
"""
import numpy as np
import cv2
import tkinter as tk
from tkinter import filedialog
from keras.models import load_model

canvas_plot_image = None
model_path = 'model_00.h5'
emotion = {0:'anger',1:'disgust',2:'fear',
            3:'happy',4:'sad',5:'surprised',6:'normal'}
model = load_model(model_path)
class GUI():
    def __init__(self,width,height):
        self.window_width = width
        self.window_height = height
        self.gui = tk.Tk()
        self.gui.title('UFace')
        self.board = tk.Canvas(self.gui,width=self.window_width,height=self.window_height)
        self.gui_init()
    def gui_init(self):
        self.g_button()
        self.board.pack()
        self.g_menu()

    def open_image(self):
        filename = filedialog.askopenfilename(initialdir='F:/')
        global canvas_plot_image
        canvas_plot_image = tk.PhotoImage(file = filename)
        width = canvas_plot_image.width()
        height = canvas_plot_image.height()
        if width>self.window_width or height > self.window_height:
            if width/self.window_width >height/self.window_height:
                canvas_plot_image.zoom(x = self.window_width/width)
            else:
                canvas_plot_image.zoom(x = self.window_height/height)
        x = int((self.window_height-width)/2)
        y = int((self.window_height-height)/2)
        self.board.create_image(x,y,anchor = tk.CENTER,image = canvas_plot_image)
    def g_menu(self):
        self.menubar = tk.Menu(self.gui)
        filemenu = tk.Menu(self.menubar,tearoff = 0)
        filemenu.add_command(label = "Open", command=self.open_image)
        filemenu.add_command(label = "Quit",command = self.gui.quit)
        #filemenu.add_separator()
        self.menubar.add_cascade(label="File", menu=filemenu)
        self.gui.config(menu = self.menubar)
    def show(self):
        self.gui.mainloop()
    def g_button(self):
        self.start_predict_button = tk.Button(master=self.gui,text = "start predict",command = self.predict).pack()
    def predict(self):
        """
        输入表情，返回表情名字，字符串。
        """
        img = cv2.cvtColor(img,cv2.COLOR_RGB2GRAY)
        img = cv2.resize(img,(48,48),interpolation=cv2.INTER_CUBIC)
        img = img.reshape([1,48,48,1])
        r = model.predict(img)
        status = np.argmax(r[0])
        emo = emotion[status]
        return emo
gui = GUI(800,600)
gui.show()