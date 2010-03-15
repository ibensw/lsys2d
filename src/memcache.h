#ifndef MEMCACHE_H
#define MEMCACHE_H
#include <stdio.h>

template <typename T>
class MemCache{
	public:
		MemCache(unsigned long size, unsigned long blocksize);
		virtual ~MemCache();
		void Shrink(unsigned long newsize);
		inline unsigned long GetSize() {return fsize;}

		const T& get(unsigned long i) const;
		T& operator[](unsigned long i);

	private:
		void ChangeBlock(unsigned long block) const;

		unsigned long fsize;
		unsigned long fblocks;
		unsigned long fblocksize;
		FILE** ffiles;
		bool* fblockexists;
		T* fblock;
		mutable unsigned long fcurrblock;
		mutable bool fcurrblockchanged;
};



template<typename T> MemCache<T>::MemCache(unsigned long size, unsigned long blocksize):
	fsize(size), fblocksize(blocksize),fcurrblock(0), fcurrblockchanged(false)
{
	fblocks=size/blocksize;
	if (size % blocksize != 0)
		fblocks++;

	fblock=new T[blocksize];

	ffiles=new FILE*[fblocks];
	fblockexists=new bool[fblocks];
	unsigned long i;
	for (i=0; i<fblocks; i++){
		ffiles[i]=tmpfile();
		fblockexists[i]=false;
		//fwrite(fblock, sizeof(T), fblocksize, ffiles[i]);
	}

	printf("Init done: %u blocks\n", (unsigned int)fblocks);
}

template<typename T> MemCache<T>::~MemCache(){
	for (unsigned long i=0; i<fblocks; i++){
		fclose(ffiles[i]);
	}

	delete []ffiles;
	delete []fblockexists;
	delete []fblock;
}

template<typename T> void MemCache<T>::ChangeBlock(unsigned long block) const{
	printf("\n Changed from block %u to %i, write changes: %i\n", (unsigned int)fcurrblock, (unsigned int)block, fcurrblockchanged?1:0);
	if (fcurrblockchanged){
		fblockexists[fcurrblock]=true;
		rewind(ffiles[fcurrblock]);
		fwrite(fblock, sizeof(T), fblocksize, ffiles[fcurrblock]);
	}

	fcurrblock=block;
	if (fblockexists[fcurrblock]){
		rewind(ffiles[fcurrblock]);
		if (!fread(fblock, sizeof(T), fblocksize, ffiles[fcurrblock])) printf("Error while reading\n");
	}


	fcurrblockchanged=false;
	printf("Done\n");
}

template<typename T> T& MemCache<T>::operator [](unsigned long i){
	if (i/fblocksize != fcurrblock){
		ChangeBlock(i/fblocksize);
	}

	fcurrblockchanged=true;
	return fblock[i%fblocksize];
}

template<typename T> const T& MemCache<T>::get(unsigned long i) const{
	if (i/fblocksize != fcurrblock){
		ChangeBlock(i/fblocksize);
	}
	return fblock[i%fblocksize];
}


#endif // MEMCACHE_H
