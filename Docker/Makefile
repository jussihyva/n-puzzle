.PHONY: all build start login stop remove create_keys print_key clean fclean

SELF_SIGNED_CRT	=	./influxdb-selfsigned.crt
SELF_SIGNED_KEY	=	./influxdb-selfsigned.key

all: start

build: $(SELF_SIGNED_CRT)
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

$(SELF_SIGNED_CRT):
	openssl req -x509 -nodes -newkey rsa:2048 \
	-keyout $(SELF_SIGNED_KEY) \
	-out $(SELF_SIGNED_CRT) \
	-days 365 \
	-subj "/C=FI/ST=Uusimaa/L=Espoo/O=/OU=Hive/CN=influxdb"
	chmod 644 $(SELF_SIGNED_CRT)
	chmod +r $(SELF_SIGNED_KEY)

clean: remove

fclean: clean
