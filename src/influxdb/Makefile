.PHONY: all build start login stop remove create_keys print_key clean fclean

SELF_SIGNED_CRT	=	./influxdb-selfsigned.crt
SELF_SIGNED_KEY	=	./influxdb-selfsigned.key

all: start

build: $(SELF_SIGNED_CRT)
	sudo docker-compose build

start: build
	sudo docker-compose up -d

login:
	sudo docker exec -it influxdb bash
	# influx  -ssl -unsafeSsl
	# create database Hive

login_grafana:
	sudo docker exec -it grafana bash

stop:
	-sudo docker kill chronograf
	-sudo docker kill grafana
	-sudo docker kill influxdb

remove: stop
	-sudo docker rm chronograf
	-sudo docker rm grafana
	-sudo docker rm influxdb

$(SELF_SIGNED_CRT):
	echo "FI\nUusimaa\n" | \
	openssl req -x509 -nodes -newkey rsa:2048 \
	-keyout $(SELF_SIGNED_KEY) \
	-out $(SELF_SIGNED_CRT) \
	-days 365 \
	-subj "/C=FI/ST=Uusimaa/L=Espoo/O=/OU=/CN="
	chmod 644 $(SELF_SIGNED_CRT)
	chmod +r $(SELF_SIGNED_KEY)

print_key:
	openssl x509 -in $(SELF_SIGNED_CRT) -text -noout

clean: remove

fclean: clean
