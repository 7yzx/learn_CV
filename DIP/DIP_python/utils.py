import cv2
import numpy as np
import matplotlib.pyplot as plt
from PIL import Image
import time

## 图像的读取
def read_image(image_path):
    image = np.array(Image.open(image_path))
    return image


## 图像的显示
def show_images(images,titles=None):
    plt.figure(figsize=(10, 6))
    for i, image in enumerate(images):
        plt.subplot(1, len(images), i + 1)
        plt.imshow(image, cmap='gray' if image.ndim == 2 else None)
        plt.title(titles[i] if titles else f'Image {i + 1}')
        plt.axis('off')
    plt.show()
    

