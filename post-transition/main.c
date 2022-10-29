#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STRING_LENGTH 6

struct package
{
	char* id;
	int weight;
};

typedef struct package package;

struct post_office
{
	int min_weight;
	int max_weight;
	package* packages;
	int packages_count;
};

typedef struct post_office post_office;

struct town
{
	char* name;
	post_office* offices;
	int offices_count;
};

typedef struct town town;



void print_all_packages(town t) {
    printf("%s:\n", t.name);
    for(int i = 0; i < t.offices_count; i++){
        printf("\t%d:\n", i);
        post_office office = t.offices[i];
        for(int j = 0; j < office.packages_count; j++){
            printf("\t\t%s\n", office.packages[j].id);
        }
    }
}

void send_all_acceptable_packages(town* source, int source_office_index, town* target, int target_office_index) {
    post_office *target_office = &(target->offices[target_office_index]);

    post_office *source_office = &(source->offices[source_office_index]);

    int packages_to_send = 0;

    for(int i = 0; i < source_office->packages_count; i++){
        package pckg = source_office->packages[i];
        if(pckg.weight >= target_office->min_weight && pckg.weight <= target_office->max_weight){
            packages_to_send++;
        }
    }

    int new_packages_count = target_office->packages_count + packages_to_send;

    package *sent_packages = calloc(new_packages_count, sizeof(package*));
    memcpy(sent_packages, target_office->packages, target_office->packages_count * sizeof(package));

    package *left_packages = calloc(source_office->packages_count - packages_to_send, sizeof(package*));

    int sent_counter = target_office->packages_count;
    int left_counter = 0;
    for(int i = 0; i < source_office->packages_count; i++){
        package pckg = source_office->packages[i];
        if(pckg.weight >= target_office->min_weight && pckg.weight <= target_office->max_weight){
            sent_packages[sent_counter] = pckg;
            sent_counter++;
        }
        else{
            left_packages[left_counter] = pckg;
            left_counter++;
        }
    }

    free(source_office->packages);
    source_office->packages_count = left_counter;
    source_office->packages = left_packages;

    free(target_office->packages);
    target_office->packages_count = new_packages_count;
    target_office->packages = sent_packages;
}

town town_with_most_packages(town* towns, int towns_count) {
    int biggestTownIndex;
    int biggestAmount = 0;

    for(int i = 0; i < towns_count; i++){
        town town = towns[i];
        int packagesCount = 0;
        for(int j = 0; j < town.offices_count; j++){
            post_office office = town.offices[j];
            packagesCount += office.packages_count;
        }
        if(packagesCount > biggestAmount){
            biggestAmount = packagesCount;
            biggestTownIndex = i;
        }
    }

    return towns[biggestTownIndex];
}

town* find_town(town* towns, int towns_count, char* name) {
    for(int i = 0; i < towns_count; i++){
        if(!(strcmp(towns[i].name, name))){
            return &towns[i];
        }
    }

    return NULL;
}

int main()
{
	int towns_count;
	scanf("%d", &towns_count);
	town* towns = malloc(sizeof(town)*towns_count);
	for (int i = 0; i < towns_count; i++) {
		towns[i].name = malloc(sizeof(char) * MAX_STRING_LENGTH);
		scanf("%s", towns[i].name);
		scanf("%d", &towns[i].offices_count);
		towns[i].offices = malloc(sizeof(post_office)*towns[i].offices_count);
		for (int j = 0; j < towns[i].offices_count; j++) {
			scanf("%d%d%d", &towns[i].offices[j].packages_count, &towns[i].offices[j].min_weight, &towns[i].offices[j].max_weight);
			towns[i].offices[j].packages = malloc(sizeof(package)*towns[i].offices[j].packages_count);
			for (int k = 0; k < towns[i].offices[j].packages_count; k++) {
				towns[i].offices[j].packages[k].id = malloc(sizeof(char) * MAX_STRING_LENGTH);
				scanf("%s", towns[i].offices[j].packages[k].id);
				scanf("%d", &towns[i].offices[j].packages[k].weight);
			}
		}
	}
	int queries;
	scanf("%d", &queries);
	char town_name[MAX_STRING_LENGTH];
	while (queries--) {
		int type;
		scanf("%d", &type);
		switch (type) {
		case 1:
			scanf("%s", town_name);
			town* t = find_town(towns, towns_count, town_name);
			print_all_packages(*t);
			break;
		case 2:
			scanf("%s", town_name);
			town* source = find_town(towns, towns_count, town_name);
			int source_index;
			scanf("%d", &source_index);
			scanf("%s", town_name);
			town* target = find_town(towns, towns_count, town_name);
			int target_index;
			scanf("%d", &target_index);
			send_all_acceptable_packages(source, source_index, target, target_index);
			break;
		case 3:
			printf("Town with the most number of packages is %s\n", town_with_most_packages(towns, towns_count).name);
			break;
		}
	}
	return 0;
}