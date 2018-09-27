"""
This is keras version resnet
"""
import keras.layers as KL
import keras.layers.normalization as KLM
import pandas as pd
import numpy as np
from tqdm import tqdm
import cv2

def get_data(filename,augment = True):
    """
    读取csv文件返回训练数据
    """
    data = pd.read_csv(filename)
    data = data.sample(frac=1)  #shuffle data
    count,_ = data.shape
    train_data = list()
    train_label = list()
    test_data = list()
    test_label = list()
    print('convert data..')
    for i in tqdm(range(count)):
        row = data.loc[i]
        img = np.array([int(ele) for ele in row[1].split()]).reshape(48,48)/255.
        if row[2] == 'Training' or row[2] == 'PublicTest':
            train_data.append(img)
            label = np.zeros(shape=[7,])
            label[row[0]] = 1
            train_label.append(label)
        else:
            test_data.append(img)
            label = np.zeros(shape=[7,])
            label[row[0]] = 1
            test_label.append(label)
    train_data = np.stack(train_data).astype(np.float32).reshape([-1,48,48,1])
    train_label = np.stack(train_label)
    test_data = np.stack(test_data).astype(np.float32).reshape([-1,48,48,1])
    test_label = np.stack(test_label)
    if augment:
        print("正在增强数据...")
        aug_img = list()
        aug_label = list()
        train_num = train_data.shape[0]
        for im in tqdm(range(train_num)):
            tempImg = train_data[im,:,:,:]
            x = cv2.flip(tempImg,1).reshape([48,48,1])
            y = cv2.flip(tempImg,0).reshape([48,48,1])
            xy = cv2.flip(tempImg,-1).reshape([48,48,1])
            label = train_label[im,:]
            aug_img.append(tempImg)
            aug_img.append(x)
            aug_img.append(y)
            aug_img.append(xy)
            for n in range(4):
                aug_label.append(label)
        aug_img = np.stack(aug_img)
        aug_label = np.stack(aug_label)
        return [aug_img,aug_label,test_data,test_label]
    return [train_data,train_label,test_data,test_label]

def get_data_for_tune(filename):
    data = pd.read_csv(filename)
    data = data.sample(frac=1)  #shuffle data
    train_data = list()
    train_label = list()
    print('convert data..')
    for i in tqdm(range(124)):
        row = data.loc[i]
        img = np.array([int(ele) for ele in row[1].split()]).reshape(48,48)/255.
        train_data.append(img)
        label = np.zeros(shape=[7,])
        label[row[0]] = 1
        train_label.append(label)

    train_data = np.stack(train_data).astype(np.float32).reshape([-1,48,48,1])
    train_label = np.stack(train_label)
    return [train_data,train_label]
def identity_block(input_tensor, kernel_size, filters, stage, block,
                   use_bias=True):
    """The identity_block is the block that has no conv layer at shortcut
    # Arguments
        input_tensor: input tensor
        kernel_size: defualt 3, the kernel size of middle conv layer at main path
        filters: list of integers, the nb_filters of 3 conv layer at main path
        stage: integer, current stage label, used for generating layer names
        block: 'a','b'..., current block label, used for generating layer names
    """
    nb_filter1, nb_filter2, nb_filter3 = filters
    conv_name_base = 'res' + str(stage) + block + '_branch'
    bn_name_base = 'bn' + str(stage) + block + '_branch'
    # 1*1 conv
    x = KL.Conv2D(nb_filter1, (1, 1), name=conv_name_base + '2a',
                  use_bias=use_bias)(input_tensor)
    x = KLM.BatchNormalization(axis=3, name=bn_name_base + '2a')(x)
    x = KL.Activation('relu')(x)
    # 3*3 conv
    x = KL.Conv2D(nb_filter2, (kernel_size, kernel_size), padding='same',
                  name=conv_name_base + '2b', use_bias=use_bias)(x)
    x = KLM.BatchNormalization(axis=3, name=bn_name_base + '2b')(x)
    x = KL.Activation('relu')(x)
    # 1*1 conv
    x = KL.Conv2D(nb_filter3, (1, 1), name=conv_name_base + '2c',
                  use_bias=use_bias)(x)
    x = KLM.BatchNormalization(axis=3, name=bn_name_base + '2c')(x)

    x = KL.Add()([x, input_tensor])
    x = KL.Activation('relu', name='res' + str(stage) + block + '_out')(x)
    return x


def conv_block(input_tensor, kernel_size, filters, stage, block,
               strides=(2, 2), use_bias=True):
    """conv_block is the block that has a conv layer at shortcut
    # Arguments
        input_tensor: input tensor
        kernel_size: defualt 3, the kernel size of middle conv layer at main path
        filters: list of integers, the nb_filters of 3 conv layer at main path
        stage: integer, current stage label, used for generating layer names
        block: 'a','b'..., current block label, used for generating layer names
    Note that from stage 3, the first conv layer at main path is with subsample=(2,2)
    And the shortcut should have subsample=(2,2) as well
    """
    nb_filter1, nb_filter2, nb_filter3 = filters
    conv_name_base = 'res' + str(stage) + block + '_branch'
    bn_name_base = 'bn' + str(stage) + block + '_branch'

    x = KL.Conv2D(nb_filter1, (1, 1), strides=strides,
                  name=conv_name_base + '2a', use_bias=use_bias)(input_tensor)
    x = KLM.BatchNormalization(axis=3, name=bn_name_base + '2a')(x)
    x = KL.Activation('relu')(x)

    x = KL.Conv2D(nb_filter2, (kernel_size, kernel_size), padding='same',
                  name=conv_name_base + '2b', use_bias=use_bias)(x)
    x = KLM.BatchNormalization(axis=3, name=bn_name_base + '2b')(x)
    x = KL.Activation('relu')(x)

    x = KL.Conv2D(nb_filter3, (1, 1), name=conv_name_base +
                  '2c', use_bias=use_bias)(x)
    x = KLM.BatchNormalization(axis=3, name=bn_name_base + '2c')(x)

    shortcut = KL.Conv2D(nb_filter3, (1, 1), strides=strides,
                         name=conv_name_base + '1', use_bias=use_bias)(input_tensor)
    shortcut = KLM.BatchNormalization(axis=3, name=bn_name_base + '1')(shortcut)

    x = KL.Add()([x, shortcut])
    x = KL.Activation('relu', name='res' + str(stage) + block + '_out')(x)
    return x


def resnet(input_image):
    # Stage 1
    x = KL.ZeroPadding2D((3, 3))(input_image)
    x = KL.Conv2D(64, (7, 7), strides=(2, 2), name='conv1', use_bias=True)(x)
    # image size become 1/2
    x = KLM.BatchNormalization(axis=3, name='bn_conv1')(x)
    x = KL.Activation('relu')(x)
    C1 = x = KL.MaxPooling2D((3, 3), strides=(2, 2), padding="same")(x)
    # image size become 1/4
    # Stage 2

    x = conv_block(x, 3, [64, 64, 256], stage=2, block='a', strides=(1, 1))
    x = identity_block(x, 3, [64, 64, 256], stage=2, block='b')
    C2 = x = identity_block(x, 3, [64, 64, 256], stage=2, block='c')
    # Stage 3
    x = conv_block(x, 3, [128, 128, 512], stage=3, block='a')
    x = identity_block(x, 3, [128, 128, 512], stage=3, block='b')
    x = identity_block(x, 3, [128, 128, 512], stage=3, block='c')
    C3 = x = identity_block(x, 3, [128, 128, 512], stage=3, block='d')
    # Stage 4
    x = conv_block(x, 3, [256, 256, 1024], stage=4, block='a')
    block_count = 2
    for i in range(block_count):
        x = identity_block(x, 3, [256, 256, 1024], stage=4, block=chr(98 + i))
    C4 = x
    return [C1, C2, C3, C4]