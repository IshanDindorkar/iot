#!/bin/bash

echo Installing docker...
curl -fsSL https://download.docker.com/linux/ubuntu/gpg | sudo apt-key add -
sudo add-apt-repository "deb [arch=amd64] https://download.docker.com/linux/ubuntu $(lsb_release -cs) stable"
sudo apt-get update
sudo apt-get install -y docker-ce

echo Creating directories for storing DBs...
mkdir ~/mosca
mkdir ~/influxdb
mkdir ~/telegraf

echo Creating docker network for our project...
sudo docker network create iot

echo Launching mosca...
sudo docker run -dt --rm --network iot --name mosca -p 1883:1883 -v ~/mosca:/db matteocollina/mosca

echo Launching influxdb...
sudo docker run -dt --rm --network iot --name influxdb -v ~/influxdb:/var/lib/influxdb influxdb:1.8
echo Waiting for servers to initialize...
sleep 3
echo Creating database...
sudo docker run -it --rm --network iot influxdb influx -host influxdb -execute 'create database mydb'

echo Creating configuration file for telegraf
cat > ~/telegraf/telegraf.conf << EOT
# Telegraf Configuration

[agent]
  omit_hostname = true

[[outputs.influxdb]]
  urls = ["http://influxdb:8086"]
  database = "mydb"

[[inputs.mqtt_consumer]]
  servers = ["mosca:1883"]
  qos = 0
  topics = [
    "sensor/#",
  ]
  data_format = "influx"
EOT

echo Launching telegraf...
sudo docker run -dt --rm --network iot --name telegraf -v ~/telegraf/telegraf.conf:/etc/telegraf/telegraf.conf:ro telegraf

echo Launching chronograf...
sudo docker run -dt --rm --network iot --name chronograf -p 10000:10000 --env PORT=10000 chronograf

echo Launching nodered...
sudo docker run -dt --rm --network iot --name nodered -v node_red_data:/data -p 1880:1880 nodered/node-red

echo Installation complete
sleep 3
sudo docker ps
