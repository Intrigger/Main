struct strIntDictonary{
	unsigned char key[50];
	int value;
};

struct strIntDictionaryVector{
	struct strIntDictonary element;
	struct strIntDictonaryVector* next;
};

struct buf{
	unsigned char value;
	struct buf* next;
};


//Функция проверена, работает
int inVector(struct strIntDictionaryVector* vec, unsigned char* key, int vecSize){
	while (vecSize--){

		int equals = 1;

		for (int i = 0; i < 50; i++){
			if (key[i] != vec->element.key[i]){
				equals = 0;
				break;
			}
		}
		if (equals == 1) return 1;

		vec = vec->next;
	}

	return 0;
}


//Функция проверена, работает
int strEquals(unsigned char* str1, unsigned char* str2){				
	if (strlen(str1) != strlen(str2)) return 0;

	for (int i = 0; i < strlen(str1); i++){
		if (str1[i] != str2[i]) return 0;
	}
	return 1;
}


void sortVectorByKey(struct strIntDictonaryVector* vec, int vecSize){

	if (vecSize == 1) return;

	int left = vecSize / 2;
	int right = vecSize - left;

	printf("Left: %d Right: %d\n", left, right);

	struct strIntDictionaryVector* vecLeft = vec;
	struct strIntDictionaryVector* vecRight = vec;


	for (int i = 0; i < left; i++) vecRight = vecRight->next;
	struct strIntDictionaryVector* vecRightCopy = vecRight;

	for (int i = 0; i < left; i++){
		char *strLeft = vecLeft->element.key;
		printf("\nLeft word: %s\n", strLeft);
		printf("Right word: ");
		for (int j = 0; j < right; j++){
			char *strRight = vecRight->element.key;
			printf("%s,", strRight);
			for (int x = 0; x < 50; x++){
				if (((int)(strLeft[x]) > (int)(strRight[x])) && (strRight[x] != 0)){

					printf("%s > %s\t --> ", strLeft, strRight);
					
					for (int x1 = 0; x1 < 50; x1++){
						unsigned char t = strLeft[x1];
						(strLeft)[x1] = (strRight)[x1];
						(strRight)[x1] = t;
					}
					printf("%s < %s\n", strLeft, strRight);
					break;
				}
				if (((int)(strLeft[x]) < (int)(strRight[x])) && (strRight[x] != 0)){
					break;
				}
			}
			if (j + 1 < right) vecRight = vecRight->next;
		}

		vecRight = vecRightCopy;

		if (i + 1 < left) vecLeft = vecLeft->next;
	}


	sortVectorByKey(vec, left);
	sortVectorByKey(vecRightCopy, right);

}