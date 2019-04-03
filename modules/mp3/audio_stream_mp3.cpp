#include "audio_stream_mp3.h"

#define MINIMP3_IMPLEMENTATION

void AudioStreamMP3::set_data(const PoolVector<uint8_t> &p_data) {

	mp3dec_init(&mp3d);
	PoolVector<uint8_t>::Read src_datar = p_data.read();
	int src_data_len = p_data.size();

	PoolVector<char> alloc_mem;
	PoolVector<char>::Write w;
	short *pcm;
	alloc_mem.resize(sizeof(short) * MINIMP3_MAX_SAMPLES_PER_FRAME);
	w = alloc_mem.write();	
	pcm = w.ptr();

	mp3dec_frame_info_t info;
	if (mp3dec_decode_frame(&mp3d, src_datar.ptr(), src_data_len, pcm, &info) == 0) {
		// throw error;
	} else {
		channels = info.channel;
		framerate = info.hz;
	}
}

void AudioStreamMP3::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_data", "data"), &AudioStreamMP3::set_data);
	ClassDB::bind_method(D_METHOD("get_data"), &AudioStreamMP3::get_data);

	ClassDB::bind_method(D_METHOD("set_loop", "enable"), &AudioStreamMP3::set_loop);
	ClassDB::bind_method(D_METHOD("has_loop"), &AudioStreamMP3::has_loop);

	ClassDB::bind_method(D_METHOD("set_loop_offset", "seconds"), &AudioStreamMP3::set_loop_offset);
	ClassDB::bind_method(D_METHOD("get_loop_offset"), &AudioStreamMP3::get_loop_offset);

	ADD_PROPERTY(PropertyInfo(Variant::POOL_BYTE_ARRAY, "data", PROPERTY_HINT_NONE, "", PROPERTY_USAGE_NOEDITOR), "set_data", "get_data");
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "loop", PROPERTY_HINT_NONE, "", PROPERTY_USAGE_NOEDITOR), "set_loop", "has_loop");
	ADD_PROPERTY(PropertyInfo(Variant::REAL, "loop_offset", PROPERTY_HINT_NONE, "", PROPERTY_USAGE_NOEDITOR), "set_loop_offset", "get_loop_offset");
}