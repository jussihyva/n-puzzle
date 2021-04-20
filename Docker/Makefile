.PHONY: all build start login stop remove create_keys print_key clean fclean

all: start

build:
	docker-compose build

start: build
	docker-compose up -d

login:
	docker exec -it n_puzzle bash

login_influxdb:
	docker exec -it influxdb bash
	# influx  -ssl -unsafeSsl
	# create database Hive

login_grafana:
	docker exec -it grafana bash

stop:
	-docker kill n_puzzle
	-docker kill chronograf
	-docker kill grafana
	-docker kill influxdb

remove: stop
	-docker rm n_puzzle
	-docker rm chronograf
	-docker rm grafana
	-docker rm influxdb

clean: remove

fclean: clean
