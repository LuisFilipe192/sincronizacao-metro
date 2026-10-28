sync_car: sync_car.c sync_car-runner.c sync_car.h
	gcc sync_car.c sync_car-runner.c -o sync_car -pthread

clean:
	rm -f sync_car