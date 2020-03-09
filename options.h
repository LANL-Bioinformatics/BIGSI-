#ifndef __OPTIONS
#define	__OPTIONS

#include <unordered_map>
#include <deque>
#include "mpi_util.h"
#include "hash.h"

// We need to protect any commas that appear in template variables
// if we are going to combine them with X Macros
#define SINGLE_ARG(...) __VA_ARGS__

struct BuildOptions
{

	// Use X Macros (https://en.wikipedia.org/wiki/X_Macro) to 
	// ensure that structure variable are correctly serialized
	#define BUILD_OPTION_MEMBERS \
		VARIABLE(std::deque<std::string>, filter_input) \
		VARIABLE(std::string, output_dir) \
		VARIABLE(std::string, log_filename) \
		VARIABLE(float, compression_threshold) \
		VARIABLE(size_t, subfilter_bits) \
		VARIABLE(bool, compress) \
		VARIABLE(bool, quit)

	#define VARIABLE(A, B) A B;
		BUILD_OPTION_MEMBERS
	#undef VARIABLE

	BuildOptions()
	{
	};
	
	BuildOptions(int argc, char* argv[])
	{
		load(argc, argv);
	};
	
	void load(int argc, char* argv[]);
	
	template<class T> friend size_t mpi_size(const T &m_obj);
	template<class T> friend unsigned char* mpi_unpack(unsigned char* m_ptr, 
		T &m_obj);
	template<class T> friend unsigned char* mpi_pack(unsigned char* m_ptr,
		const T &m_obj);
};

template<> size_t mpi_size(const BuildOptions &m_obj);
template<> unsigned char* mpi_pack(unsigned char* m_ptr, const BuildOptions &m_obj);
template<> unsigned char* mpi_unpack(unsigned char* m_ptr, BuildOptions &m_obj);

struct SearchOptions
{

	// Allowed output file formats
	enum {
		OUTPUT_CSV,
		OUTPUT_JSON
	};
	
	// Use X Macros (https://en.wikipedia.org/wiki/X_Macro) to 
	// ensure that structure variable are correctly serialized
	#define SEARCH_OPTION_MEMBERS \
		VARIABLE(std::deque<std::string>, query_files) \
		VARIABLE(std::deque<std::string>, query_seq) \
		VARIABLE(std::deque<std::string>, subject_files) \
		VARIABLE(std::string, output_file) \
		VARIABLE(float, threshold) \
		VARIABLE(unsigned int, output_format) \
		VARIABLE(bool, quit)

	#define VARIABLE(A, B) A B;
		SEARCH_OPTION_MEMBERS
	#undef VARIABLE

	SearchOptions(int argc, char* argv[]);
};

struct DownloadOptions
{

	// Use X Macros (https://en.wikipedia.org/wiki/X_Macro) to 
	// ensure that structure variable are correctly serialized
	#define DOWNLOAD_OPTION_MEMBERS \
		VARIABLE(std::string, metadata_file) \
		VARIABLE(std::string, download_dir) \
		VARIABLE(std::string, bloom_dir) \
		VARIABLE(std::string, log_file) \
		VARIABLE(float, false_positive_probability) \
		VARIABLE(unsigned int, kmer_len) \
		VARIABLE(unsigned int, min_kmer_count) \
		VARIABLE(HashFunction, hash_func) \
		VARIABLE(unsigned int, max_num_download_attempts) \
		VARIABLE(unsigned int, sleep_interval) \
		VARIABLE(unsigned int, max_backlog) \
		VARIABLE(unsigned int, num_download_threads) \
		VARIABLE(bool, list_only) \
		VARIABLE(bool, quit)

	#define VARIABLE(A, B) A B;
		DOWNLOAD_OPTION_MEMBERS
	#undef VARIABLE

	DownloadOptions()
	{
	};
	
	DownloadOptions(int argc, char* argv[])
	{
		load(argc, argv);
	};
	
	void load(int argc, char* argv[]);
	
	template<class T> friend size_t mpi_size(const T &m_obj);
	template<class T> friend unsigned char* mpi_unpack(unsigned char* m_ptr, 
		T &m_obj);
	template<class T> friend unsigned char* mpi_pack(unsigned char* m_ptr,
		const T &m_obj);
};

template<> size_t mpi_size(const DownloadOptions &m_obj);
template<> unsigned char* mpi_pack(unsigned char* m_ptr, const DownloadOptions &m_obj);
template<> unsigned char* mpi_unpack(unsigned char* m_ptr, DownloadOptions &m_obj);

struct BloomerOptions
{

	// Use X Macros (https://en.wikipedia.org/wiki/X_Macro) to 
	// ensure that structure variable are correctly serialized
	#define BLOOMER_OPTION_MEMBERS \
		VARIABLE(std::string, input_dir) \
		VARIABLE(std::string, output_file) \
		VARIABLE(float, false_positive_probability) \
		VARIABLE(unsigned int, min_kmer_count) \
		VARIABLE(unsigned int, kmer_len) \
		VARIABLE(unsigned int, num_file_slice) \
		VARIABLE(HashFunction, hash_func) \
		VARIABLE(bool, save_sra) \
		VARIABLE(bool, read_meta_data) \
		VARIABLE(bool, verbose) \
		VARIABLE(bool, quit)

	#define VARIABLE(A, B) A B;
		BLOOMER_OPTION_MEMBERS
	#undef VARIABLE

	BloomerOptions()
	{
	};
	
	BloomerOptions(int argc, char* argv[])
	{
		load(argc, argv);
	};
	
	void load(int argc, char* argv[]);
	
	template<class T> friend size_t mpi_size(const T &m_obj);
	template<class T> friend unsigned char* mpi_unpack(unsigned char* m_ptr, 
		T &m_obj);
	template<class T> friend unsigned char* mpi_pack(unsigned char* m_ptr,
		const T &m_obj);
};

template<> size_t mpi_size(const BloomerOptions &m_obj);
template<> unsigned char* mpi_pack(unsigned char* m_ptr, const BloomerOptions &m_obj);
template<> unsigned char* mpi_unpack(unsigned char* m_ptr, BloomerOptions &m_obj);

// The maximum number of groups (i.e. Bloom filters) per file
#define		NUM_FILTER_CHUNK				2048u
#define		MIN_NUM_FILTERS_FOR_COMPRESSION			64 // Require this many Bloom filters in a slice before compressing
#define		DEFAULT_FALSE_POSITIVE_PROBABILITY		0.25f // Per k-mer
#define		DEFAULT_SUBFILTER_BITS				1024
#define		DEFAULT_COMPRESSION_THRESHOLD			0.75
#define		DEFAULT_KMER_LENGTH				31
#define		DEFAULT_SRA_MIN_KMER_COUNT			5
#define		DEFAULT_NUM_SRA_FILE_SLICE			5
#define		MAX_SRA_FILE_SLICE				128
#define		DEFAULT_SEARCH_THRESHOLD 			1.0f
#define		DEFAULT_SEARCH_OUTPUT 				SearchOptions::OUTPUT_JSON
#define		DEFAULT_DOWNLOAD_ATTEMPT			5
#define		DEFAULT_HASH_FUNCTION				MURMUR_HASH
#define		DEFAULT_MAX_BACKLOG				25
#define		DEFAULT_DOWNLOAD_THREADS			1

#endif // __OPTIONS
