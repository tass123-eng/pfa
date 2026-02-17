# Pest Detection Ensemble System - Raspberry Pi 4 B+

## 🎯 Overview
This is an optimized pest detection system that runs on Raspberry Pi 4 B+, combining CNN and YOLO models for accurate pest classification with an intelligent ensemble approach.

## 🚀 Key Optimizations for Raspberry Pi

### Memory Management
- **Reduced batch size** (8 instead of 32) to fit in 4GB RAM
- **Streaming inference** for YOLO to avoid loading all images at once
- **Memory cleanup** after each major operation using garbage collection
- **TensorFlow Lite** optimizations with CPU-only mode

### CPU Optimization
- **Multi-threading** configured for 4 cores (Raspberry Pi 4)
- **Batch processing** with periodic memory cleanup
- **Headless matplotlib** (Agg backend) for image generation without GUI

### Model Inference
- **Efficient data generators** with reduced augmentation
- **Optimized batch prediction** for CNN
- **Stream-based YOLO inference** in smaller batches
- **Memory-aware ensemble** computation

## 📋 Requirements

### Hardware
- Raspberry Pi 4 B+ (4GB RAM recommended)
- MicroSD card (32GB+ recommended)
- Adequate cooling (heat sink or fan)

### Software
- Raspbian OS (Bullseye or later)
- Python 3.7+
- pip package manager

## 🔧 Installation

### 1. System Update
```bash
sudo apt-get update
sudo apt-get upgrade -y
```

### 2. Install System Dependencies
```bash
# Essential build tools
sudo apt-get install -y python3-pip python3-dev
sudo apt-get install -y libatlas-base-dev libopenblas-dev
sudo apt-get install -y libjpeg-dev libtiff5-dev libpng-dev
sudo apt-get install -y libavcodec-dev libavformat-dev libswscale-dev libv4l-dev
sudo apt-get install -y libhdf5-dev libhdf5-serial-dev

# OpenCV dependencies
sudo apt-get install -y libqtgui4 libqt4-test
```

### 3. Create Virtual Environment (Recommended)
```bash
cd /home/pi/pfa
python3 -m venv venv
source venv/bin/activate
```

### 4. Install Python Packages
```bash
# Upgrade pip
pip install --upgrade pip

# Install requirements
pip install -r requirements.txt
```

**Note for TensorFlow on Raspberry Pi:**
If the standard TensorFlow installation fails, use:
```bash
pip install tensorflow-aarch64
# or for older Pi models:
pip install https://github.com/PINTO0309/Tensorflow-bin/releases/download/v2.11.0/tensorflow-2.11.0-cp39-none-linux_armv7l.whl
```

## 📁 Dataset Structure

Organize your dataset in the following structure:

```
/home/pi/pfa/dataset/
├── train/
│   ├── class1/
│   │   ├── img1.jpg
│   │   └── img2.jpg
│   ├── class2/
│   └── ...
├── val/
│   ├── class1/
│   └── class2/
└── test/
    ├── class1/
    └── class2/
```

If you have a single directory with all images, you can split it:
```bash
python3 -c "from pfa_mixage import split_dataset; split_dataset('source_dir', '/home/pi/pfa/dataset')"
```

## 🔑 Model Setup

Place your trained models in the models directory:

```
/home/pi/pfa/models/
├── cnn_pest_best.h5      # Your trained CNN model
└── yolo_best.pt          # Your trained YOLO model
```

## 🏃 Usage

### Basic Usage
```bash
# Run on test set (default)
python3 pfa_mixage.py

# Run on validation set
python3 pfa_mixage.py --split val

# Specify custom paths
python3 pfa_mixage.py \
    --data-root /path/to/dataset \
    --cnn-model /path/to/cnn_model.h5 \
    --yolo-model /path/to/yolo_model.pt

# Adjust batch size for your memory constraints
python3 pfa_mixage.py --batch-size 4  # Use smaller batch if OOM occurs
```

### Command Line Arguments
- `--split`: Dataset split to evaluate (train/val/test, default: test)
- `--data-root`: Path to dataset root directory
- `--cnn-model`: Path to CNN model file (.h5)
- `--yolo-model`: Path to YOLO model file (.pt)
- `--batch-size`: Batch size for inference (default: 8)

### Example
```bash
python3 pfa_mixage.py --split test --batch-size 8
```

## 📊 Output

Results are saved to `/home/pi/pfa/outputs/`:
- `model_comparison.png` - Accuracy comparison chart
- `Smart_Ensemble_Test_Set.png` - Confusion matrix
- `roc_curve.png` - ROC curve (macro average)
- `pest_detection_results.png` - Detection examples
- Console output with detailed metrics

## ⚙️ Configuration

Edit the `Config` class in `pfa_mixage.py` to customize:

```python
class Config:
    # Paths
    DATA_ROOT = "/home/pi/pfa/dataset"
    MODEL_DIR = "/home/pi/pfa/models"
    
    # Performance tuning
    BATCH_SIZE = 8          # Reduce if OOM
    IMG_SIZE = (224, 224)   # Keep this for model compatibility
    
    # Ensemble parameters
    ALPHA = 0.85  # YOLO weight
    BETA = 0.15   # CNN weight
    CONFIDENCE_THRESHOLD = 0.75
    
    # Detection settings
    TARGET_CLASS = "Grasshopper"
    CONF_THRESHOLD_PERCENT = 70
```

## 🐛 Troubleshooting

### Out of Memory (OOM) Errors
```bash
# Reduce batch size
python3 pfa_mixage.py --batch-size 4

# Close other applications
# Increase swap space:
sudo dphys-swapfile swapoff
sudo nano /etc/dphys-swapfile  # Set CONF_SWAPSIZE=2048
sudo dphys-swapfile setup
sudo dphys-swapfile swapon
```

### Slow Performance
```bash
# Enable CPU governor performance mode
sudo apt-get install cpufrequtils
sudo cpufreq-set -g performance

# Monitor temperature
vcgencmd measure_temp
```

### TensorFlow Import Errors
```bash
# Try alternative TensorFlow build
pip uninstall tensorflow
pip install tensorflow-cpu

# Or use TensorFlow Lite
pip install tflite-runtime
```

### YOLO Installation Issues
```bash
# Install specific torch version for ARM
pip install torch==1.13.0 torchvision==0.14.0 --index-url https://download.pytorch.org/whl/cpu

# Then install ultralytics
pip install ultralytics
```

## 🎨 Features

### 1. Dual Model Inference
- **CNN**: EfficientNet-based classifier
- **YOLO**: YOLOv8 classification

### 2. Ensemble Methods
- **Weighted Ensemble**: Combines predictions with fixed weights (85% YOLO, 15% CNN)
- **Smart Ensemble**: Adapts weighting based on CNN confidence

### 3. Comprehensive Evaluation
- Accuracy metrics for each model
- Confusion matrices
- ROC curves
- Per-class performance reports

### 4. Detection Demo
- Visual detection results with confidence scores
- Target pest detection (configurable)

## 📈 Performance Tips

### Optimize for Speed
1. Use smaller batch sizes (4-8)
2. Reduce image resolution if accuracy allows
3. Enable CPU performance mode
4. Close unnecessary background processes

### Optimize for Accuracy
1. Use larger batch sizes (8-16) if memory allows
2. Keep original image resolution
3. Tune ensemble weights (ALPHA/BETA)
4. Adjust confidence threshold

## 🔄 Converting Models

### Convert Keras Model to TensorFlow Lite
```python
import tensorflow as tf

# Load model
model = tf.keras.models.load_model('cnn_pest_best.h5')

# Convert to TFLite
converter = tf.lite.TFLiteConverter.from_keras_model(model)
converter.optimizations = [tf.lite.Optimize.DEFAULT]
tflite_model = converter.convert()

# Save
with open('cnn_pest_best.tflite', 'wb') as f:
    f.write(tflite_model)
```

## 📝 License
[Your License Here]

## 👥 Contributors
Optimized for Raspberry Pi by [Your Name]

## 📧 Support
For issues or questions, please open an issue on GitHub or contact [your-email@example.com]
