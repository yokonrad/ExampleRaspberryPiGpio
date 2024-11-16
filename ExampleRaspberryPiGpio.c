#include <stdio.h>
#include <unistd.h>

const char *validDrinkTypes[] = {"coffee", "tea", "water"};
const char *validDrinkSizes[] = {"small", "medium", "big"};

#define GPIO_DRINK_TYPE_COFFEE 17
#define GPIO_DRINK_TYPE_TEA 27
#define GPIO_DRINK_TYPE_WATER 37

#define DURATION_DRINK_SIZE_SMALL 3
#define DURATION_DRINK_SIZE_MEDIUM 4
#define DURATION_DRINK_SIZE_BIG 5

bool isDrinkTypeFilled(char* drinkType) {
	if(drinkType && drinkType[0]) return true;
	
	printf("Drink type is empty.\n");
	
	return false;
}

bool isDrinkSizeFilled(char* drinkSize) {
	if(drinkSize && drinkSize[0]) return true;
	
	printf("Drink size is empty.\n");
	
	return false;
}

int getDrinkTypeKey(char* drinkType) {
	int array_count = sizeof(validDrinkTypes) / sizeof(*validDrinkTypes);

    for (int i = 0; i < array_count; i++) {
        if (!strcmp(validDrinkTypes[i], drinkType)) {
			return i;
        }
    }
	
	printf("Invalid drink type. Passed value: %s\n", drinkType);
	
	return -1;
}

int getDrinkSizeKey(char* drinkSize) {
	int array_count = sizeof(validDrinkSizes) / sizeof(*validDrinkSizes);

    for (int i = 0; i < array_count; i++) {
        if (!strcmp(validDrinkSizes[i], drinkSize)) {
			return i;
        }
    }
	
	printf("Invalid drink size. Passed value: %s\n", drinkSize);
	
	return -1;
}

int getDrinkGpio(int drinkTypeKey) {
	switch (drinkTypeKey) {
		case 0:
			return GPIO_DRINK_TYPE_COFFEE;
			
		case 1:
			return GPIO_DRINK_TYPE_TEA;
			
		case 2:
			return GPIO_DRINK_TYPE_WATER;
			
		default:
			return -1;
	}
}

int getDrinkDuration(int drinkSizeKey) {
	switch (drinkSizeKey) {
		case 0:
			return DURATION_DRINK_SIZE_SMALL;
			
		case 1:
			return DURATION_DRINK_SIZE_MEDIUM;
			
		case 2:
			return DURATION_DRINK_SIZE_BIG;
			
		default:
			return -1;
	}
}

void initGpio() {
	// https://github.com/WiringPi/WiringPi GPIO library for Raspberry Pi
	// GPIO init
}

void activatePinForDuration(int gpio, int duration) {
	//pinMode(gpio, OUTPUT); // sets the digital pin as OUTPUT
	//digitalWrite(gpio, HIGH); // sets the digital pin as HIGH
	
	sleep(duration);
	
	//digitalWrite(gpio, LOW); // sets the digital pin as LOW
}

void drinkPrepare(char* drinkType, char* drinkSize, int drinkGpio, int drinkDuration) {
	initGpio();
	
	printf("Selected drink: %s with size: %s\n", drinkType, drinkSize);
	printf("Found GPIO of drink: %i and duration of: %i seconds\n", drinkGpio, drinkDuration);
	printf("Starting drink preparation...\n");
	printf("Dispensing %s for %i seconds...\n", drinkType, drinkDuration);
	
	activatePinForDuration(drinkGpio, drinkDuration);
	
	printf("Drink preparation complete!\n");
}

int main(int argc, char **argv) {	
	char* drinkType = argv[1];
	char* drinkSize = argv[2];
	
	if (!isDrinkTypeFilled(drinkType)) return 0;
	if (!isDrinkSizeFilled(drinkSize)) return 0;
	
	int drinkTypeKey = getDrinkTypeKey(drinkType);
	int drinkSizeKey = getDrinkSizeKey(drinkSize);
	
	if (drinkTypeKey < 0) return 0;
	if (drinkSizeKey < 0) return 0;
	
	int drinkGpio = getDrinkGpio(drinkTypeKey);
	int drinkDuration = getDrinkDuration(drinkSizeKey);
	
	drinkPrepare(drinkType, drinkSize, drinkGpio, drinkDuration);

	return 1;
}
