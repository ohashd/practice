#include <stdio.h>
#include <string.h>

static const char b64chars[65] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
static char b64decs[256] = {0};
static bool built=false;


//Assumes ret is big enough for atleast 1+4*ceil(strlen(orig)/3) characters
void b64Encode(const char *orig, char*ret){
	int len = strlen(orig);

	for(int i=2;i<len;i+=3){ //process body of string in 3's
		int buff=orig[i];
		buff |= (orig[i-1] << 8);
		buff |= (orig[i-2] << 16);
		*(ret++)=b64chars[(buff >> 18) & 63];
		*(ret++)=b64chars[(buff >> 12) & 63];
		*(ret++)=b64chars[(buff >> 6) & 63];
		*(ret++)=b64chars[(buff) & 63];
	}
	if(len%3==1){ //2 encoded chars, 2 padding
		int buff = orig[len-1];
		*(ret++)=b64chars[(buff >> 2) &63];
		*(ret++)=b64chars[(buff << 4) &63];
		*(ret++)='=';
		*(ret++)='=';
	}else if(len%3==2){//3 encoded chars, 1 padding
		int buff = orig[len-1];
		buff |= orig[len-2] << 8;
		*(ret++)=b64chars[(buff >> 10) &63];
		*(ret++)=b64chars[(buff >> 4) &63];
		*(ret++)=b64chars[(buff << 2) &63];
		*(ret++)='=';
	}
	*ret='\0';
}

void buildB64Decs(){
	for(int i=0;i<256;i++){
		b64decs[i]=-1;
	}
	for(int i=0;i<64;i++){
		b64decs[int(b64chars[i])]=i;
	}
}

//Assumes ret is big enough for atleast 3*ceil(strcspn(orig,"=\0")/4)
bool b64Decode(const char *orig, char*ret){

	int len = strcspn(orig,"=\0");
	int totlen = strlen(orig);
	//impossible for totlen to have 1 excess character in groups of 4
	//and impossible to have more than 2 padding characters
	if(len<totlen-2 || totlen%4==1){
		return false;
	}

	if(!built){
		built=true;
		buildB64Decs();
	}


	for(int i = 3;i<len;i+=4){ //process in 4s
		int ind1 = b64decs[(int)(orig[i-3])];
		int ind2 = b64decs[(int)(orig[i-2])];
		int ind3 = b64decs[(int)(orig[i-1])];
		int ind4 = b64decs[(int)(orig[i])];
		if(ind1==-1 || ind2==-1 || ind3==-1 || ind4==-1) return false;
		int buff= (ind1 <<18) | (ind2 << 12) | (ind3 << 6) | ind4;
		*(ret++)=(buff >> 16) & 255;
		*(ret++)=(buff >> 8) & 255;
		*(ret++)=(buff) & 255;
	}
	if(len%4==2){ //2 padding =s
		int ind1 = b64decs[(int)(orig[len-2])];
		int ind2 = b64decs[(int)(orig[len-1])];
		if(ind1==-1 || ind2==-1) return false;
		int buff= (ind1 <<6) | ind2;
		*(ret++)=(buff >> 4) & 255;
	}else if(len%4==3){ //1 padding =s
		int ind1 = b64decs[(int)(orig[len-3])];
		int ind2 = b64decs[(int)(orig[len-2])];
		int ind3 = b64decs[(int)(orig[len-1])];
		if(ind1==-1 || ind2==-1 || ind3==-1) return false;
		int buff= (ind1 <<12) | (ind2 << 6) | ind3;
		*(ret++)=(buff >> 10) & 255;
		*(ret++)=(buff >> 2) & 255;
	}

	*ret='\0';
	return true;
}

int main(){
	char inp[90],enc[120];
	if(NULL==fgets(inp,90,stdin))return 1;
	inp[strcspn(inp,"\n")]=0;

	b64Encode(inp,enc);
	if(b64Decode(enc,inp)){
		printf("Decrypted: %s\n",inp);
	}else{
		printf("Invalid Base 64 String");
	}

	printf("Encrypted: %s\n",enc);
}