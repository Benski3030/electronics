####Connecting to Device
sudo screen /dev/ttyUSB0 115200


https://github.com/MarsTechHAN/M5-VTraining/blob/master/m5TrainingService.py#L287


### Useful Links

#### Environment Setup

Install kflash

Install MaixPyIDE

Install nncase

[Environment Notes](http://community.m5stack.com/topic/1226/m5stickv-link-info-dump)


#### Projects
https://colab.research.google.com/drive/1mirG8BSoB3k87mh-qyY3-8-ZXj0XB6h6#scrollTo=CJ5_9MQQxM_b


[Cheering Watch of M5StickC&V](https://m5stack.hackster.io/anoken2017/cheering-watch-of-m5stickc-v-34f0cc)


[Desk-Robot Assistant](https://m5stack.hackster.io/jarain78/desk-robot-assistant-based-on-m5stick-v-and-m5stack-09c8e9)

[Transfer Learning](https://bbs.sipeed.com/t/topic/1050/3)
[M5StickVersion](https://gist.github.com/kotobuki/65b06e10be209607bf9ca63748564ee9)
[Example Code](https://docs.m5stack.com/#/en/related_documents/M5StickV-Maixpy)




`~/nncase/ncc compile model/iris.tflite k210/kpu_iris_example/iris.kmodel -i tflite -o kmodel -t k210 --inference-type float`




`~/Apps/nncase/ncc compile ~/Documents/Special_Projects/Skunk_Detector/code/skunkerlt.tflite ~/Documents/Special_Projects/Skunk_Detector/code/skunk.kmodel --dataset ~/Documents/Special_Projects/Skunk_Detector/data/train -i tflite -o kmodel -t k210`


~/Apps/nncase/ncc  ~/Documents/Special_Projects/Skunk_Detector/code/skunker.tflite  ~/Documents/Special_Projects/Skunk_Detector/code/skunker.kmodel  -i tflite -o k210model --dataset ~/Documents/Special_Projects/Skunk_Detector/data/train --inference-type float

https://github.com/datitran/raccoon_dataset/tree/master/training

https://github.com/kendryte/nncase/releases/download/v0.1.0-rc5/ncc-linux-x86_64.tar.xz

wget https://github.com/kendryte/nncase/releases/download/v0.1.0-rc5/ncc-linux-x86_64.tar.xz