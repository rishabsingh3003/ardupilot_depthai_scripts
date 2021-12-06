# DepthAI Scripts for ArduPilot
This repository contains scripts as well as instructions on how to integrate DepthAI Cameras with ArduCopter.
Currently, only the IoT series of cameras are supported as they can be used in a plug-and-play scenario without any additional companion computer.

![Demo](IOT/docs/images/body_track.gif)

## Installation for IOT devices

1. Install DepthAI.
- Install pre-requisites from the instructions [here](https://docs.luxonis.com/projects/api/en/latest/install/)
- Install DepthAI version 2.13.2.0
```bash
python3 -m pip install depthai==2.13.2.0
```

2. For IoT devices, install IDF via the guide [here](https://docs.espressif.com/projects/esp-idf/en/v4.2.2/esp32/get-started/index.html). Please make sure you install version 4.2.2 ONLY.

3. Clone this project and its submodules:
``` bash
git clone https://github.com/rishabsingh3003/ardupilot_depthai_scripts.git

git submodule update --recursive --init
```
4. Navigate to the Project you would like to test (follow_me, obstacle_avoidnace, precision_landing) for the next steps

## Contributing
Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.

## License
[GPLv2](https://www.gnu.org/licenses/old-licenses/gpl-2.0.en.html)
