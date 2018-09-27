"""
UFace 主文件，显示图形界面以及计算
"""
import numpy as np
import cv2
import tkinter as tk
from tkinter import filedialog
from keras.models import load_model
from resnet import get_data_for_tune

canvas_plot_image = None
model_path = 'F:/DataPool/UFace_data/model_00.h5'
new_train_model_path = 'F:/DataPool/UFace_data/model_train_tune.h5'
fer2013_file_path = 'F:/DataPool/UFace_data/fer2013.csv'
emotion = {0:'anger',1:'disgust',2:'fear',
            3:'happy',4:'sad',5:'surprised',6:'normal'}
#总是优先加载微调过的模型
try:
    model = load_model(new_train_model_path)
except:
    model = load_model(model_path)

class GUI():
    def __init__(self,width,height):
        self.window_width = width
        self.window_height = height
        self.emo_class_info = "Not Detect Yet!"
        self.gui = tk.Tk()
        self.gui.title('UFace')
        self.board = tk.Canvas(self.gui,width=self.window_width,height=self.window_height)
        self.gui_init()
    def gui_init(self):
        self.g_label()
        self.g_button()
        self.g_menu()
        self.welcome_label.pack()
        self.expression_info_label.pack()
        self.board.pack()

    def open_image(self):
        try:
            filename = filedialog.askopenfilename(initialdir='/home/kara')
            self.image_name = filename
            global canvas_plot_image
            canvas_plot_image = tk.PhotoImage(file = filename)
            #width = canvas_plot_image.width()
            #height = canvas_plot_image.height()
            """
            if width>self.window_width or height > self.window_height:
                if width/self.window_width >height/self.window_height:
                    canvas_plot_image.zoom(x = self.window_width/width)
                else:
                    canvas_plot_image.zoom(x = self.window_height/height)
            """
            #x = int((self.window_height-width)/2)
            #y = int((self.window_height-height)/2)
            from skimage.io import imread
            
            self.meta_image = imread(filename)
            self.board.create_image(200,50,anchor = 'nw',image = canvas_plot_image)
            self.start_predict_button.pack()
        except:
            self.expression_info_label['text'] = "Opps,check file type and try again"
    def g_menu(self):
        self.menubar = tk.Menu(self.gui)
        filemenu = tk.Menu(self.menubar,tearoff = 0)
        filemenu.add_command(label = "Open", command=self.open_image)
        #filemenu.add_command(label = "Help",command = self.gui.quit)
        #filemenu.add_separator()
        self.menubar.add_cascade(label="File", menu=filemenu)
        #debug
        editmenu = tk.Menu(self.menubar,tearoff = 0)
        editmenu.add_command(label = "train model",command = self.train_model)
        self.menubar.add_cascade(label = "Edit",menu = editmenu)
        self.gui.config(menu = self.menubar)
    def show(self):
        self.gui.mainloop()
    def g_button(self):
        self.start_predict_button = tk.Button(master=self.gui,text = "start predict",command = self.predict)
    def g_label(self):
        self.expression_info_label = tk.Label(master=self.gui,text = "Tips: Click File to Open File")
        self.welcome_label = tk.Label(master=self.gui,text = "Welcome Using UFace :)")
    def predict(self):
        """
        输入表情，返回表情名字，字符串。
        """
        shape = self.meta_image.shape
        img = cv2.resize(self.meta_image,(48,48),interpolation=cv2.INTER_CUBIC)
        if len(shape)>2:
            img = cv2.cvtColor(img , cv2.COLOR_RGB2GRAY)
        img = img.reshape([1,48,48,1])/255.
        r = model.predict(img)
        status = np.argmax(r[0])
        self.emo_class_info = emotion[status]
        self.expression_info_label['text'] = "The expression is: "+ self.emo_class_info + "!"
    def train_model(self):
        """
        重新训练模型，加强模型性能
        """
        try:
            train_img = self._get_and_augment_data()
            b_train_data,b_train_label = get_data_for_tune(fer2013_file_path)
            class_info_num,train_label = self.parser_image_name()
            train_imgs = np.concatenate((train_img,b_train_data),axis = 0)
            train_labels = np.concatenate((train_label,b_train_label),axis = 0)
            #debug
            if train_label is None:
                return 
            while True:
                self.expression_info_label['text'] = "正在训练模型中..."
                model.fit(train_imgs,train_labels,epochs = 1,batch_size =16)
                cls_info = model.predict(train_img)
                #print(cls_info)
                cls_info = np.argmax(cls_info[3])
                if cls_info == class_info_num:
                    self.expression_info_label['text']="训练完成,保存模型中..."
                    model.save(filepath = new_train_model_path)
                    self.expression_info_label['text'] = '模型已保存'
                    break
                self.expression_info_label['text'] = "未达到效果，继续训练中..."
        except:
            self.expression_info_label['text'] = 'Please load image first...'

    def parser_image_name(self):
        """
        解析文件名，返回one_hot真值
        """
        name = self.image_name
        emotion_label = {'anger':0,'disgust':1,'fear':2,
            'happy':3,'sad':4,'surprised':5,'normal':6}
        class_info_number = None
        for flag in emotion_label:
            if flag in name:
                class_info_number = emotion_label[flag]
        if class_info_number is None:
            self.expression_info_label['text'] = '命名不符合规范，无法训练！！'
            return None
        else:
            one_hot_label = np.zeros(shape=[4,7])
            one_hot_label[:,class_info_number] = 1
            return [class_info_number,one_hot_label]
    def _get_and_augment_data(self):
        """
        data augment 
        """
        shape = self.meta_image.shape
        img = cv2.resize(self.meta_image,(48,48),interpolation=cv2.INTER_CUBIC)
        if len(shape)>2:
            img = cv2.cvtColor(img , cv2.COLOR_RGB2GRAY)
        x = cv2.flip(img,1).reshape([48,48,1])/255.
        y = cv2.flip(img,0).reshape([48,48,1])/255.
        xy = cv2.flip(img,-1).reshape([48,48,1])/255.
        img = img.reshape([48,48,1])/255.
        train_img = np.stack([x,y,xy,img])
        return train_img
gui = GUI(800,400)
gui.show()