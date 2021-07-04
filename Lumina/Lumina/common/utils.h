#ifndef utils_h

#define utils_h

#include "../sdk/math/Vector.h"
#include "../sdk/structs/mystructs.h"
#include "../sdk/structs/Entity.h"

#include <vector>
#include "../sdk/structs/structs.h"

struct WavFileHeader {
	char chunk_id[4];
	int chunk_size;
	char format[4];
	char subchunk1_id[4];
	int subchunk1_size;
	short int audio_format;
	short int num_channels;
	int sample_rate;
	int byte_rate;
	short int block_align;
	short int bits_per_sample;
	char subchunk2_id[4];
	int subchunk2_size;
};

struct WavFile {
	WavFileHeader* buffer;
	DWORD size;

	WavFile(WavFileHeader* buffer, DWORD size) {
		this->buffer = buffer;
		this->size = size;
	}
};


namespace utils
{
	std::vector<paint_kit> getSkinsInfo();
	bool getEntityBox(Entity* ent, box& in);
	bool precacheModel(const char* szModelName);

	bool FileExists(const std::string& name);
	WavFileHeader* ReadWavFileHeader(std::string fname);
	int GetWavDuration(struct WavFileHeader* hdr);
	void WriteFileFromBuffer(std::string file, BYTE* buffer, int size);
}

#endif // !utils_h