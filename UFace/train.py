from resnet import resnet
from resnet import get_data
import keras.layers as KL
#import keras.backend as KB
import keras.optimizers as KO
import keras.models as KM
import random
import matplotlib.pyplot as plt
import numpy as np
from keras.models import load_model
import os
#from keras.callbacks import LearningRateScheduler
os.environ['CUDA_VISIBLE_DEVICES'] = '1 '
emotion = {0:'anger',1:'disgust',2:'fear',
            3:'happy',4:'sad',5:'surprised',6:'normal'}


def check_data():
    """
    检查数据是否正确
    """   
    id = random.randint(0,train_img.shape[0])
    img = train_img[id,:,:,:].reshape(48,48)
    emo = emotion[np.argmax(train_label[id,:])]
    plt.imshow(img,cmap = 'gray')
    plt.axis('off')
    plt.title(emo)
    
#check_data()
    
    
data_file_name = 'data/fer2013.csv'
train_img,train_label,test_img,test_label = get_data(data_file_name)

def get_model():
    input_image = KL.Input(shape=(48,48,1))
    c1,c2,c3,c4 = resnet(input_image)
    x = KL.MaxPool2D(pool_size=(3,3),name='maxpool')(c4)
    x = KL.Flatten()(x)
    x = KL.Dense(1024,activation='relu',name='fc1')(x)
    #x = KL.Dense(512,activation='relu',name='fc2')(x)
    out = KL.Dense(7,activation='softmax',name='softmax')(x)
    
    model = KM.Model(inputs=input_image,outputs=out)
    
    sgd = KO.SGD(lr=0.0005, decay=1e-6, momentum=0.9, nesterov=True)
    #adam =KO.adam(lr = 0.002)
    model.compile(loss='categorical_crossentropy',
                  optimizer=sgd,
                  metrics=['accuracy'])
    return model
#callbacks 

#load model
model_path = 'model_resnet50_1.h5'
#model = load_model(model_path)
model = get_model()
#train
model.fit(train_img, train_label,
          epochs=2,
          batch_size=128)
model.save(filepath='model_00.h5')
score = model.evaluate(test_img, test_label, batch_size=128,verbose=1)
print('test,acc:',score)