import numpy as np
import cv2
import matplotlib.pyplot as plt
from keras.models import load_model


#imagepath = 'data/test/001.png'
model_path = 'model.h5'

def plot(img,emo):
    plt.imshow(img)
    plt.axis('off')
    plt.title(emo)

model = load_model(model_path)
emotion = {0:'anger',1:'disgust',2:'fear',
            3:'happy',4:'sad',5:'surprised',6:'normal'}
def predict(img):
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
img = cv2.imread(imagepath)
img = cv2.cvtColor(img, cv2.COLOR_BGR2RGB) 

input_image = gray_img.reshape([1,48,48,1])
r = model.predict(input_image)

status = np.argmax(r[0])
emo = emotion[status]
plot(img,emo)
