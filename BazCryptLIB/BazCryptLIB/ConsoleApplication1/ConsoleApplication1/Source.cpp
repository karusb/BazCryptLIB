// USRPDLL_DEBUG.cpp : Defines the entry point for the console application.

#include <uhd.h>
#include <uhd/utils/thread_priority.hpp>
#include <uhd/utils/safe_main.hpp>
#include <uhd/usrp/multi_usrp.hpp>
#include <uhd/exception.hpp>
#include <uhd/types/tune_request.hpp>

#include <boost/format.hpp>
#include <boost/thread.hpp>

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <fstream>
#include <complex>
#include <csignal>
#include <objbase.h>
// Define CONDEBUG for console debugging
//#define CONDEBUG
#define EXECUTE_OR_GOTO(label, ...) \
    if(__VA_ARGS__){ \
        return_code = EXIT_FAILURE; \
        goto label; \
    }

std::string device_argsG("addr=192.168.10.2");
std::string subdevG("A:0"); // sub device or daughter board
std::string antG("RX-A");
std::string refG("internal"); // reference clock
size_t samplesG = 10000;
double rateG = 0;
double gainG = 1.0;
size_t channelG = 0;
double bandwidthG = 100000;
uhd::usrp::multi_usrp::sptr usrpG = NULL; // usrp device pointer
uhd::tx_streamer::sptr tx_streamG;
uhd::rx_metadata_t RXmdG; // Metadata
uhd::tx_metadata_t TXmdG;
uhd::stream_args_t stream_argsG("fc32", "sc16"); // device sample return types

static std::vector<std::complex<float>> *samplebufferGFL; // template for other types??
static std::vector<std::complex<double>> *samplebufferGDB;
static std::vector<std::complex<short>> *samplebufferGSH;

double time_requested = 0.0;
static bool stopsignal = false; // it was static before
static bool contRXG = false; // Determines if the usrp is started in continuous stream
static int DBLformat = 2;
static boost::system_time limtimeG;
static boost::system_time endtimeG;
boost::system_time start;

boost::posix_time::time_duration ticks_diff;
//uhd::stream_cmd_t command_argsG = 0;
uhd::rx_streamer::sptr rxstreamG;
uhd::tx_streamer::sptr txstreamG;
void sig_int_handler(int) { stopsignal = true; }
// DATA SEPARATORS FOR 64 BIT and 32 BIT Mixed Data
//void separate32bit(float IQ, float* I, float* Q)
//{
//	*I = (((int)IQ << 16) & 0b0000000011111111);
//	*Q = (((int)IQ) & 0b0000000011111111);
//}
//void separate32bitD(float IQ, double* I, double* Q)
//{
//	*I = (double)(((int)IQ << 16) & 0b0000000011111111);
//	*Q = (double)(((int)IQ) & 0b0000000011111111);
//}
//void separate64bit(double IQ, double* I, double* Q)
//{
//	*I = (((int)IQ << 32) & 0b00000000000000001111111111111111);
//	*Q = (((int)IQ) & 0b00000000000000001111111111111111);
//}
// std complex builder
//////// TX FUNCS //////////
extern "C" __declspec(dllexport) void USRPSetTxRate(double rate)
{
	usrpG->set_tx_rate(rate);
}
extern "C" __declspec(dllexport) double USRPGetTxRate(void)
{
	return usrpG->get_tx_rate();
}
extern "C" __declspec(dllexport) int USRPGetMaxTXSize()
{
	return tx_streamG->get_max_num_samps();
}
extern "C" __declspec(dllexport) void USRPSetTxFrequency(double freq, double lo_off = 0, bool integertuning = false)
{
	uhd::tune_request_t tune_request;
	if (lo_off != 0) tune_request = uhd::tune_request_t(freq, lo_off);
	else tune_request = uhd::tune_request_t(freq);
	if (integertuning) tune_request.args = uhd::device_addr_t("mode_n=integer");
}
extern "C" __declspec(dllexport) double USRPGetTxFrequency(void)
{
	return usrpG->get_tx_rate();
}
extern "C" __declspec(dllexport) void USRPSetTxGain(double gain)
{
	usrpG->set_tx_gain(gain);
}
extern "C" __declspec(dllexport) double USRPGetTxGain(void)
{
	return usrpG->get_tx_gain();
}
extern "C" __declspec(dllexport) void USRPSetTxBW(double bw)
{
	usrpG->set_tx_bandwidth(bw);
}
extern "C" __declspec(dllexport) double USRPGetTxBW(void)
{
	return usrpG->get_tx_bandwidth();
}
extern "C" __declspec(dllexport) void USRPSetTXAntenna(const char* ant)
{
	// set the antenna
	antG = std::string(ant);

	usrpG->set_tx_antenna(antG);
}
extern "C" __declspec(dllexport) int USRPStartTX(float* Iin, float* Qin)
{
	tx_streamG = usrpG->get_tx_stream(stream_argsG);
	TXmdG.start_of_burst = false;
	TXmdG.end_of_burst = false;
	for (int i = 0; i < samplesG; ++i)
	{
		samplebufferGFL->push_back(std::complex<float>(Iin[i], Qin[i]));
	}

	return tx_streamG->send(&samplebufferGFL->front(), samplesG, TXmdG);

}
extern "C" __declspec(dllexport) int USRPStartTXDB(double* Iin, double* Qin)
{
	tx_streamG = usrpG->get_tx_stream(stream_argsG);
	TXmdG.start_of_burst = false;
	TXmdG.end_of_burst = false;
	for (int i = 0; i < samplesG; ++i)
	{
		samplebufferGDB->push_back(std::complex<double>(Iin[i], Qin[i]));
	}

	return tx_streamG->send(&samplebufferGDB->front(), samplesG, TXmdG);
}
extern "C" __declspec(dllexport) int USRPStartTXSH(short* Iin, short* Qin)
{
	tx_streamG = usrpG->get_tx_stream(stream_argsG);
	TXmdG.start_of_burst = false;
	TXmdG.end_of_burst = false;
	for (int i = 0; i < samplesG; ++i)
	{
		samplebufferGSH->push_back(std::complex<short>(Iin[i], Qin[i]));
	}

	return tx_streamG->send(&samplebufferGSH->front(), samplesG, TXmdG);
}
extern "C" __declspec(dllexport) int USRPStartTXFile(const char* filename)
{

	tx_streamG = usrpG->get_tx_stream(stream_argsG);
	TXmdG.start_of_burst = false;
	TXmdG.end_of_burst = false;
	std::vector<float> buff(samplesG);
	std::ifstream infile(filename, std::ifstream::binary);

	//loop until the entire file has been read

	while (not TXmdG.end_of_burst) {

		infile.read((char*)&buff.front(), buff.size() * sizeof(float));
		size_t num_tx_samps = infile.gcount() / sizeof(float);

		TXmdG.end_of_burst = infile.eof();

		tx_streamG->send(&buff.front(), num_tx_samps, TXmdG);
	}

	infile.close();
}
extern "C" __declspec(dllexport) int USRPStartTXFileDB(const char* filename)
{

	tx_streamG = usrpG->get_tx_stream(stream_argsG);
	TXmdG.start_of_burst = false;
	TXmdG.end_of_burst = false;
	std::vector<double> buff(samplesG);
	std::ifstream infile(filename, std::ifstream::binary);

	//loop until the entire file has been read

	while (not TXmdG.end_of_burst) {

		infile.read((char*)&buff.front(), buff.size() * sizeof(double));
		size_t num_tx_samps = infile.gcount() / sizeof(double);

		TXmdG.end_of_burst = infile.eof();

		tx_streamG->send(&buff.front(), num_tx_samps, TXmdG);
	}

	infile.close();
}
extern "C" __declspec(dllexport) int USRPStartTXFileSH(const char* filename)
{

	tx_streamG = usrpG->get_tx_stream(stream_argsG);
	TXmdG.start_of_burst = false;
	TXmdG.end_of_burst = false;
	std::vector<short> buff(samplesG);
	std::ifstream infile(filename, std::ifstream::binary);

	//loop until the entire file has been read

	while (not TXmdG.end_of_burst) {

		infile.read((char*)&buff.front(), buff.size() * sizeof(short));
		size_t num_tx_samps = infile.gcount() / sizeof(short);

		TXmdG.end_of_burst = infile.eof();

		tx_streamG->send(&buff.front(), num_tx_samps, TXmdG);
	}

	infile.close();
}

extern "C" __declspec(dllexport) void USRPSetTXStream()
{
	tx_streamG = usrpG->get_tx_stream(stream_argsG);
	TXmdG.start_of_burst = false;
	TXmdG.end_of_burst = false;
}


/////////////////////////////



std::complex<float> buildcomplexD(float I, float Q)
{
	return std::complex<float>(I, Q);
}
extern "C" __declspec(dllexport) int FFTUHDPlan(const char* device_args, const char* subdevin, const char* antin, const char* refclk, double freq, double samplefrequency, double samplesize, double bandwidth, double gain, int window, double* Iout, double* Qout, double* FFTxout)
{
	///////////////////
	// UHD VARS
	//const char iparg = "\"addr=\"" + ip;
	//std::string device_args(ip);
	//std::string device_args("addr=192.168.10.2");
	//std::string device_args(""); // device select
	//std::string subdev(subdevin); // sub device or daughter board
	////std::string subdev("A:0"); // sub device or daughter board
	////std::string ant("RX-A"); // antenna 
	//std::string ant(antin); // antenna 
	////std::string ref("internal"); // reference clock
	//std::string ref(refclk); // reference clock
	double time_requested = 2.0; // TODO: wait time
	double sample_timeout = 3.0; // TODO: sample wait time
	double setup_time = 1.0; // initial antenna setup time

							 //int option = 0;
							 //double freq = 500e6;
	double rate = samplefrequency;
	//double gain = 5.0;
	size_t channel = 0;
	if (antin != "0")channel = 1;


	size_t n_samples = (size_t)samplesize;
	bool verbose = false;
	int return_code = EXIT_SUCCESS;

	char error_string[512];

	//// FFT VAR
	//std::complex<double> *complexbuffer = new std::complex<double>[samplesize];
	//if (!complexbuffer)return 10;

	//// UHD SETUP
	// Create USRP
	uhd_usrp_handle usrp;
	fprintf(stderr, "Creating USRP with args \"%s\"...\n", device_args);
	EXECUTE_OR_GOTO(free_option_strings,
		uhd_usrp_make(&usrp, device_args)
	)

		// Create RX streamer
		uhd_rx_streamer_handle rx_streamer;
	EXECUTE_OR_GOTO(free_usrp,
		uhd_rx_streamer_make(&rx_streamer)
	)

		// Create RX metadata
		uhd_rx_metadata_handle md;
	EXECUTE_OR_GOTO(free_rx_streamer,
		uhd_rx_metadata_make(&md)
	)

		// Create other necessary structs
		uhd_tune_request_t tune_request;
	tune_request.target_freq = freq;
	tune_request.rf_freq_policy = UHD_TUNE_REQUEST_POLICY_AUTO;
	tune_request.dsp_freq_policy = UHD_TUNE_REQUEST_POLICY_AUTO;

	uhd_tune_result_t tune_result;

	uhd_stream_args_t stream_args;
	stream_args.cpu_format = "fc32";
	stream_args.otw_format = "sc16";
	stream_args.args = "";
	stream_args.channel_list = &channel;
	stream_args.n_channels = 1;


	uhd_stream_cmd_t stream_cmd;
	stream_cmd.stream_mode = UHD_STREAM_MODE_NUM_SAMPS_AND_DONE;
	stream_cmd.num_samps = n_samples;
	stream_cmd.stream_now = true;

	size_t samps_per_buff = samplesize;/////////////////////////////////////////////////////////////////////////////////
	float *buff = (float*)malloc(samps_per_buff * 2 * sizeof(float));
	void **buffs_ptr = NULL;
	//FILE *fp = NULL;
	size_t num_acc_samps = 0;

	// Set rate
	fprintf(stderr, "Setting RX Rate: %f...\n", rate);
	EXECUTE_OR_GOTO(free_rx_metadata,
		uhd_usrp_set_rx_rate(usrp, rate, channel)
	)

		// See what rate actually is
		EXECUTE_OR_GOTO(free_rx_metadata,
			uhd_usrp_get_rx_rate(usrp, channel, &rate)
		)
		fprintf(stderr, "Actual RX Rate: %f...\n", rate);

	// Set gain
	fprintf(stderr, "Setting RX Gain: %f dB...\n", gain);
	EXECUTE_OR_GOTO(free_rx_metadata,
		uhd_usrp_set_rx_gain(usrp, gain, channel, "")
	)

		// See what gain actually is
		EXECUTE_OR_GOTO(free_rx_metadata,
			uhd_usrp_get_rx_gain(usrp, channel, "", &gain)
		)
		fprintf(stderr, "Actual RX Gain: %f...\n", gain);

	// Set frequency
	fprintf(stderr, "Setting RX frequency: %f MHz...\n", freq / 1e6);
	EXECUTE_OR_GOTO(free_rx_metadata,
		uhd_usrp_set_rx_freq(usrp, &tune_request, channel, &tune_result)
	)

		// See what frequency actually is
		EXECUTE_OR_GOTO(free_rx_metadata,
			uhd_usrp_get_rx_freq(usrp, channel, &freq)
		)
		fprintf(stderr, "Actual RX frequency: %f MHz...\n", freq / 1e6);

	// Set up streamer
	stream_args.channel_list = &channel;
	EXECUTE_OR_GOTO(free_rx_streamer,
		uhd_usrp_get_rx_stream(usrp, &stream_args, rx_streamer)
	)

		// Set up buffer
		EXECUTE_OR_GOTO(free_rx_streamer,
			uhd_rx_streamer_max_num_samps(rx_streamer, &samps_per_buff)
		)
		fprintf(stderr, "Buffer size in samples: %zu\n", samps_per_buff);
	buffs_ptr = (void**)&buff;

	// Issue stream command
	fprintf(stderr, "Issuing stream command.\n");
	EXECUTE_OR_GOTO(free_buffer,
		uhd_rx_streamer_issue_stream_cmd(rx_streamer, &stream_cmd)
	)

		// Set up file output
		//fp = fopen(filename, "wb");

		// Actual streaming
		while (num_acc_samps < n_samples) {
			size_t num_rx_samps = 0;
			EXECUTE_OR_GOTO(close_file,
				uhd_rx_streamer_recv(rx_streamer, buffs_ptr, samps_per_buff, &md, 3.0, false, &num_rx_samps)
			)

				uhd_rx_metadata_error_code_t error_code;
			EXECUTE_OR_GOTO(close_file,
				uhd_rx_metadata_error_code(md, &error_code)
			)
				if (error_code != UHD_RX_METADATA_ERROR_CODE_NONE) {
					fprintf(stderr, "Error code 0x%x was returned during streaming. Aborting.\n", return_code);
					goto close_file;
				}
			// Handle data
			//fwrite(buff, sizeof(float) * 2, num_rx_samps, fp);
			// Handle data
			//float* Iop = new float(0);
			//float* Qop = new float(0);
			int it = 0;
			for (int i = 0; i < n_samples * 2 - 1; i += 2)
			{
				//Iout[i] = buff[i];
				//separate32bit(buff[i], Iop, Qop);
				Iout[it] = buff[i];
				Qout[it] = buff[i + 1];
				std::cout << buff[i] << " and " << buff[i + 1] << std::endl;
				//std::cout << Iout[i] << " and " << Qout[i];
				it += 1;
			}
			time_t full_secs;
			double frac_secs;
			uhd_rx_metadata_time_spec(md, &full_secs, &frac_secs);
			fprintf(stderr, "Received packet: %zu samples, %.f full secs, %f frac secs\n",
				num_rx_samps,
				difftime(full_secs, (time_t)0),
				frac_secs);


			num_acc_samps += num_rx_samps;

			// Cleanup
		close_file:
			//	fclose(fp);

		free_buffer:
			if (buff) {
				if (verbose) {
					fprintf(stderr, "Freeing buffer.\n");
				}
				free(buff);
				//delete[] buff;
			}
			buff = NULL;
			buffs_ptr = NULL;

		free_rx_streamer:
			if (verbose) {
				fprintf(stderr, "Cleaning up RX streamer.\n");
			}
			uhd_rx_streamer_free(&rx_streamer);

		free_rx_metadata:
			if (verbose) {
				fprintf(stderr, "Cleaning up RX metadata.\n");
			}
			uhd_rx_metadata_free(&md);

		free_usrp:
			if (verbose) {
				fprintf(stderr, "Cleaning up USRP.\n");
			}
			if (return_code != EXIT_SUCCESS && usrp != NULL) {
				uhd_usrp_last_error(usrp, error_string, 512);
				fprintf(stderr, "USRP reported the following error: %s\n", error_string);
			}
			uhd_usrp_free(&usrp);

		free_option_strings:
			if (strcmp(device_args, "")) {
				//free(device_args);
				//delete device_args;
			}
			//if (custom_filename) {
			//	free(filename);
			//}

			fprintf(stderr, (return_code ? "Failure\n" : "Success\n"));
			return return_code;
		}
}
extern "C" __declspec(dllexport) int FFTUHDPlanP(const char* device_args, const char* subdevin, const char* antin, const char* refclk, double freq, double samplefrequency, double samplesize, double bandwidth, double gain, int window, double* Iout, double* Qout, double* FFTxout)
{

	///////////////////
	// UHD VARS
	//uhd::usrp::multi_usrp::sptr usrp = uhd::usrp::multi_usrp::make(args);
	//const char iparg = "\"addr=\"" + ip;
	std::string device_argss("addr=192.168.10.2"); // device select ///////////////////////////////////////////////////////////
	std::string subdev("A:0"); // sub device or daughter board/ //////////////////////////////////////////////
	std::string ant("RX-A"); // antenna							/////////////////////////////////////////////////
	std::string ref("internal"); // reference clock				//////////////////////////////////////////////
	double time_requested = 2.0; // TODO: wait time
	double sample_timeout = 3.0; // TODO: sample wait time
	double setup_time = 1.0; // initial antenna setup time

							 //int option = 0;
							 //double freq = 500e6;
	double rate = samplefrequency;
	//double gain = 5.0;
	size_t channel = 0;
	if (antin != "0")channel = 1;


	size_t n_samples = (size_t)samplesize;


	//FFT VAR
	std::complex<double> *complexbuffer = new std::complex<double>[samplesize];
	if (!complexbuffer)return 10;

	// UHD SETUP

	////// C ++ IMPLEMENTATION OF USRP ////////////////
	/****************************************************************************************/
	std::vector<std::string> sensor_names; // Sensor name vector
	size_t buflimit = samplesize;						// Determines the sample per buffer
	std::vector<std::complex<double>> samplebuffer(buflimit); // template for other types??

	typedef std::map<size_t, size_t> SizeMap; //std map def 
	SizeMap mapSizes;

	uhd::rx_metadata_t RXmd; // Metadata

							 // Stream args obj with data types
							 /*
							 fc64 complex double
							 fc32 complex float
							 sc16 complex int16_t
							 sc8 complex int8_t
							 */
	uhd::stream_args_t stream_args("fc32", "sc16");

	// Set stream channels
	//stream_args.channels = boost::assign::list_of(0);
	// optional samples per packet
	//stream_args.args["spp"] = "200";
	//char  *data;
	//data = new char[1e6];


	//create a usrp device
	std::cout << std::endl;
	std::cout << boost::format("Creating the usrp device with: %s...") % device_args << std::endl;
	uhd::usrp::multi_usrp::sptr usrp = uhd::usrp::multi_usrp::make(std::string(device_args));
	//std::cin >> aa;

	// LO , REF Check	with error handling
	//sensor_names = usrp->get_rx_sensor_names(0); // ?
	//int sensor_count = sensor_names.begin();
	//while (sensor_count != sensor_names.end)std::cout << sensor_names.at(sensor_count);


	// Lock mboard clocks
	std::cout << boost::format("Lock mboard clocks: %f") % ref << std::endl;
	usrp->set_clock_source(ref);
	//std::cin >> aa;
	//always select the subdevice first, the channel mapping affects the other settings

	// TODO: EXCEPTION THROWN
	std::cout << boost::format("subdev set to: %f") % subdev << std::endl;
	//usrp->set_rx_subdev_spec(subdev);
	std::cout << boost::format("Using Device: %s") % usrp->get_pp_string() << std::endl;

	//set the sample rate
	if (samplefrequency <= 0.0) {
		std::cerr << "Please specify a valid sample rate" << std::endl;
		return ~0;
	}

	// set sample rate
	std::cout << boost::format("Setting RX Rate: %f Msps...") % (samplefrequency / 1e6) << std::endl;
	usrp->set_rx_rate(samplefrequency);
	std::cout << boost::format("Actual RX Rate: %f Msps...") % (usrp->get_rx_rate() / 1e6) << std::endl << std::endl;

	//std::cin >> aa;

	// set freq
	std::cout << boost::format("Setting RX Freq: %f MHz...") % (freq / 1e6) << std::endl;
	uhd::tune_request_t tune_request(freq);
	usrp->set_rx_freq(tune_request);
	std::cout << boost::format("Actual RX Freq: %f MHz...") % (usrp->get_rx_freq() / 1e6) << std::endl << std::endl;

	// set the rf gain
	std::cout << boost::format("Setting RX Gain: %f dB...") % gain << std::endl;
	usrp->set_rx_gain(gain);
	std::cout << boost::format("Actual RX Gain: %f dB...") % usrp->get_rx_gain() << std::endl << std::endl;

	// set the IF filter bandwidth
	std::cout << boost::format("Setting RX Bandwidth: %f MHz...") % (bandwidth / 1e6) << std::endl;
	usrp->set_rx_bandwidth(bandwidth);
	// TODO : EXCEPTION THROWN
	//std::cout << boost::format("Actual RX Bandwidth: %f MHz...") % (usrp->get_rx_bandwidth() / 1e6) << std::endl << std::endl;

	// set the antenna
	std::cout << boost::format("Setting RX Antenna: %s") % ant << std::endl;
	usrp->set_rx_antenna(ant);
	boost::this_thread::sleep(boost::posix_time::seconds(setup_time)); //allow for some setup time

																	   // TODO: EXCEPTION THROWN ????? Check
																	   //std::cout << boost::format("Actual RX Antenna: %s") % usrp->get_rx_antenna() << std::endl << std::endl;
																	   //usrp->get_rx_sensor(data, 1e6);#

	std::cout << boost::format("Set Configuration: %s") % usrp->get_pp_string() << std::endl;
	// STREAM SETUP
	uhd::stream_cmd_t command_args((samplesize == 0) ?
		uhd::stream_cmd_t::STREAM_MODE_START_CONTINUOUS :
		uhd::stream_cmd_t::STREAM_MODE_NUM_SAMPS_AND_DONE);
	// obvious stream setups
	command_args.num_samps = size_t(samplesize);
	command_args.stream_now = true;
	command_args.time_spec = uhd::time_spec_t();
	uhd::rx_streamer::sptr rxstream = usrp->get_rx_stream(stream_args);
	usrp->issue_stream_cmd(command_args); // START STREAM

										  // RECV HERE
	size_t received_samples = rxstream->recv(&samplebuffer.front(), samplebuffer.size(), RXmd, sample_timeout, false);
	/**************************************************************************************************************/

	//RETURN DATA TYPES?????
	int fol = 0;
	for (std::vector<std::complex<double>>::iterator it = samplebuffer.begin(); it != samplebuffer.end() && fol <= samplesize; ++it)
	{
		Iout[fol] = it->real();
		Qout[fol] = it->imag();

		fol += 1;
	}

	delete[] complexbuffer;

	return 200;
}
extern "C" __declspec(dllexport) bool USRPConnection(const char* args)
{
	device_argsG = std::string(args);
#ifdef CONDEBUG
	std::cout << boost::format("Creating the usrp device with: %s...") % device_argsG << std::endl;
#endif
	try
	{
		usrpG = uhd::usrp::multi_usrp::make(device_argsG);
	}
	catch (uhd::key_error e)
	{
#ifdef CONDEBUG
		std::cout << "USRP CANNOT BE FOUND" << std::endl;
#endif
		return false;
	}
	return true;
}
extern "C" __declspec(dllexport) void USRPSetCLK(const char* clk)
{
	refG = std::string(clk);
#ifdef CONDEBUG
	std::cout << boost::format("Lock mboard clocks: %f") % refG << std::endl;
#endif
	usrpG->set_clock_source(refG);
}
extern "C" __declspec(dllexport) void USRPSetSamplingRate(double smprate)
{
	// set sample rate
	rateG = smprate;
	usrpG->set_rx_rate(smprate);
#ifdef CONDEBUG
	std::cout << boost::format("Setting RX Rate: %f Msps...") % (rateG / 1e6) << std::endl;
	std::cout << boost::format("Actual RX Rate: %f Msps...") % (usrpG->get_rx_rate() / 1e6) << std::endl << std::endl;
#endif	

}

extern "C" __declspec(dllexport) double USRPGetSamplingRate(void)
{
	return usrpG->get_rx_rate();
}
extern "C" __declspec(dllexport) void USRPSetFrequency(double fr)
{


	uhd::tune_request_t tune_request(fr);
	usrpG->set_rx_freq(tune_request);
#ifdef CONDEBUG
	std::cout << boost::format("Setting RX Freq: %f MHz...") % (fr / 1e6) << std::endl;
	std::cout << boost::format("Actual RX Freq: %f MHz...") % (usrpG->get_rx_freq() / 1e6) << std::endl << std::endl;
#endif
}
extern "C" __declspec(dllexport) double USRPGetFrequency()
{
	return usrpG->get_rx_freq();

}
extern "C" __declspec(dllexport) void USRPSetGain(double gn)
{
	// set the rf gain
	gainG = gn;
	usrpG->set_rx_gain(gainG);
#ifdef CONDEBUG
	std::cout << boost::format("Setting RX Gain: %f dB...") % gainG << std::endl;
	std::cout << boost::format("Actual RX Gain: %f dB...") % usrpG->get_rx_gain() << std::endl << std::endl;
#endif
}
extern "C" __declspec(dllexport) double USRPGetGain(void)
{
	return usrpG->get_rx_gain();
	//return gainG;
}
extern "C" __declspec(dllexport) void USRPSetBW(double BW)
{
	// set the IF filter bandwidth
	bandwidthG = BW;
	usrpG->set_rx_bandwidth(bandwidthG);
#ifdef CONDEBUG
	std::cout << boost::format("Setting RX Bandwidth: %f MHz...") % (bandwidthG / 1e6) << std::endl;
#endif
	// TODO : EXCEPTION THROWN
	//std::cout << boost::format("Actual RX Bandwidth: %f MHz...") % (usrpG->get_rx_bandwidth() / 1e6) << std::endl << std::endl;
}
extern "C" __declspec(dllexport) void USRPSetAntenna(const char* ant)
{
	// set the antenna
	antG = std::string(ant);

	usrpG->set_rx_antenna(antG);
#ifdef CONDEBUG
	std::cout << boost::format("Setting RX Antenna: %s") % antG << std::endl;
#endif
	boost::this_thread::sleep(boost::posix_time::seconds(1)); //allow for some setup time
}
extern "C" __declspec(dllexport) void USRPSetDataFormat(int format)
{
	if (format == 3)
	{
		DBLformat = 3;
		stream_argsG = uhd::stream_args_t("fc64", "sc16");
	}
	else if (format == 2)
	{
		DBLformat = 2;
		stream_argsG = uhd::stream_args_t("fc32", "sc16");
	}
	else if (format == 1)
	{
		DBLformat = 1;
		stream_argsG = uhd::stream_args_t("sc16", "sc16");
	}


}
extern "C" __declspec(dllexport) void USRPSetSampleSize(int sz)
{
	samplesG = sz;
	if (DBLformat == 3)
	{
		samplebufferGDB = new std::vector<std::complex<double>>((size_t)sz);
	}
	else if (DBLformat == 2)
	{
		samplebufferGFL = new std::vector<std::complex<float>>((size_t)sz);
	}
	else if (DBLformat == 1)
	{
		samplebufferGSH = new std::vector<std::complex<short>>((size_t)sz);
	}

}
extern "C" __declspec(dllexport) int USRPGetSampleSize(void)
{
	/// TODO: OTHER TYPES??
	return samplebufferGFL->size();
}
extern "C" __declspec(dllexport) void USRPSetRXStream(bool mode = false)
{
	contRXG = mode;
	stream_argsG.args["fullscale"] = "1.0";
	uhd::stream_cmd_t command_argsG((mode == true) ?
		uhd::stream_cmd_t::STREAM_MODE_START_CONTINUOUS :
		uhd::stream_cmd_t::STREAM_MODE_NUM_SAMPS_AND_DONE);
	// obvious stream setups 
	command_argsG.num_samps = size_t(samplesG);
	command_argsG.stream_now = true;
	//command_argsG.stream_now = false;
	command_argsG.time_spec = uhd::time_spec_t();
	//command_argsG.time_spec = uhd_usrp_set_command_time();
	//command_argsG.time_spec = uhd::time_spec_t(0.001);
	rxstreamG = usrpG->get_rx_stream(stream_argsG);

	usrpG->issue_stream_cmd(command_argsG); // START STREAM
	limtimeG = boost::get_system_time();
#ifdef CONDEBUG
	std::cout << "Max Sample: " << rxstreamG->get_max_num_samps() << std::endl;
#endif
	//if (samplesG == 0) USRPSetSampleSize(rxstreamG->get_max_num_samps());
}
extern "C" __declspec(dllexport) void USRPSetRequestTime(double tim)
{
	time_requested = tim;
}
extern "C" __declspec(dllexport) int USRPStartRX(float* Iout, float* Qout)
{
	start = boost::get_system_time();
	//std::cout << boost::format("Set Configuration: %s") % usrpG->get_pp_string() << std::endl;

	unsigned long long ticks_requested = (long)(time_requested * (double)boost::posix_time::time_duration::ticks_per_second());
	size_t received_samples = 0;
	boost::system_time last_update = start;
	unsigned long long last_update_samps = 0;
	// RECV HERE

	received_samples = rxstreamG->recv(&samplebufferGFL->front(), samplebufferGFL->size(), RXmdG, 3, false);

	/**************************************************************************************************************/
	////handle the error code
	if (RXmdG.error_code == uhd::rx_metadata_t::ERROR_CODE_TIMEOUT) return -5;
	if (RXmdG.error_code == uhd::rx_metadata_t::ERROR_CODE_OVERFLOW) return -10;
	if (RXmdG.error_code == uhd::rx_metadata_t::ERROR_CODE_LATE_COMMAND) return -15;
	if (RXmdG.error_code != uhd::rx_metadata_t::ERROR_CODE_NONE) return -99;
#ifdef CONDEBUG
	std::cout << boost::format(
		"Received packet: %u samples, %u full secs, %f frac secs"
	) % received_samples % RXmdG.time_spec.get_full_secs() % RXmdG.time_spec.get_frac_secs() << std::endl;


	if (RXmdG.more_fragments)std::cout << "Fragmented data, offset: " << (int)RXmdG.fragment_offset << std::endl;
#endif

	int fol = 0;


	for (std::vector<std::complex<float>>::iterator it = samplebufferGFL->begin(); it != samplebufferGFL->end(); ++it)
	{
		Iout[fol] = it->real();
		Qout[fol] = it->imag();

		fol += 1;
	}

	boost::system_time now = boost::get_system_time();
	boost::posix_time::time_duration timelimit = now - limtimeG;
	last_update_samps += received_samples;
	boost::posix_time::time_duration update_diff = now - last_update;
	if (update_diff.ticks() > boost::posix_time::time_duration::ticks_per_second()) {
		double t = (double)update_diff.ticks() / (double)boost::posix_time::time_duration::ticks_per_second();
		double r = (double)last_update_samps / t;
#ifdef CONDEBUG
		std::cout << boost::format("\t%f Msps") % (r / 1e6) << std::endl;
#endif
		last_update_samps = 0;
		last_update = now;
	}


	ticks_diff = now - start;

	// TYPE ERROR BELOW ?
	if ((double)timelimit.ticks() / (double)boost::posix_time::time_duration::ticks_per_second() >= (double)time_requested)stopsignal = true;
	//std::cout << "Time : " << (double)timelimit.ticks() / (double)boost::posix_time::time_duration::ticks_per_second() << std::endl;
	return received_samples;
}
extern "C" __declspec(dllexport) int USRPStartRXDBL(double* Iout, double* Qout)
{
	start = boost::get_system_time();
	//std::cout << boost::format("Set Configuration: %s") % usrpG->get_pp_string() << std::endl;

	unsigned long long ticks_requested = (long)(time_requested * (double)boost::posix_time::time_duration::ticks_per_second());
	size_t received_samples = 0;
	boost::system_time last_update = start;
	unsigned long long last_update_samps = 0;
	// RECV HERE

	received_samples = rxstreamG->recv(&samplebufferGDB->front(), samplebufferGDB->size(), RXmdG, 3, false);


	/**************************************************************************************************************/
	////handle the error code
	if (RXmdG.error_code == uhd::rx_metadata_t::ERROR_CODE_TIMEOUT) return -5;
	if (RXmdG.error_code == uhd::rx_metadata_t::ERROR_CODE_OVERFLOW) return -10;
	if (RXmdG.error_code == uhd::rx_metadata_t::ERROR_CODE_LATE_COMMAND) return -15;
	if (RXmdG.error_code != uhd::rx_metadata_t::ERROR_CODE_NONE) return -99;
#ifdef CONDEBUG
	std::cout << boost::format(
		"Received packet: %u samples, %u full secs, %f frac secs"
	) % received_samples % RXmdG.time_spec.get_full_secs() % RXmdG.time_spec.get_frac_secs() << std::endl;


	if (RXmdG.more_fragments)std::cout << "Fragmented data, offset: " << (int)RXmdG.fragment_offset << std::endl;
#endif

	int fol = 0;

	for (std::vector<std::complex<double>>::iterator it = samplebufferGDB->begin(); it != samplebufferGDB->end(); ++it)
	{
		Iout[fol] = it->real();
		Qout[fol] = it->imag();

		fol += 1;
	}



	boost::system_time now = boost::get_system_time();
	boost::posix_time::time_duration timelimit = now - limtimeG;
	last_update_samps += received_samples;
	boost::posix_time::time_duration update_diff = now - last_update;
	if (update_diff.ticks() > boost::posix_time::time_duration::ticks_per_second()) {
		double t = (double)update_diff.ticks() / (double)boost::posix_time::time_duration::ticks_per_second();
		double r = (double)last_update_samps / t;
#ifdef CONDEBUG
		std::cout << boost::format("\t%f Msps") % (r / 1e6) << std::endl;
#endif
		last_update_samps = 0;
		last_update = now;
	}


	ticks_diff = now - start;

	// TYPE ERROR BELOW ?
	if ((double)timelimit.ticks() / (double)boost::posix_time::time_duration::ticks_per_second() >= (double)time_requested)stopsignal = true;
	//std::cout << "Time : " << (double)timelimit.ticks() / (double)boost::posix_time::time_duration::ticks_per_second() << std::endl;
	return received_samples;
}
extern "C" __declspec(dllexport) int USRPStartRXSH(short* Iout, short* Qout)
{
	start = boost::get_system_time();
	//std::cout << boost::format("Set Configuration: %s") % usrpG->get_pp_string() << std::endl;

	unsigned long long ticks_requested = (long)(time_requested * (double)boost::posix_time::time_duration::ticks_per_second());
	size_t received_samples = 0;
	boost::system_time last_update = start;
	unsigned long long last_update_samps = 0;
	// RECV HERE

	received_samples = rxstreamG->recv(&samplebufferGSH->front(), samplebufferGSH->size(), RXmdG, 3, false);

	/**************************************************************************************************************/
	////handle the error code
	if (RXmdG.error_code == uhd::rx_metadata_t::ERROR_CODE_TIMEOUT) return -5;
	if (RXmdG.error_code == uhd::rx_metadata_t::ERROR_CODE_OVERFLOW) return -10;
	if (RXmdG.error_code == uhd::rx_metadata_t::ERROR_CODE_LATE_COMMAND) return -15;
	if (RXmdG.error_code != uhd::rx_metadata_t::ERROR_CODE_NONE) return -99;
#ifdef CONDEBUG
	std::cout << boost::format(
		"Received packet: %u samples, %u full secs, %f frac secs"
	) % received_samples % RXmdG.time_spec.get_full_secs() % RXmdG.time_spec.get_frac_secs() << std::endl;


	if (RXmdG.more_fragments)std::cout << "Fragmented data, offset: " << (int)RXmdG.fragment_offset << std::endl;
#endif

	int fol = 0;


	for (std::vector<std::complex<short>>::iterator it = samplebufferGSH->begin(); it != samplebufferGSH->end(); ++it)
	{
		Iout[fol] = it->real();
		Qout[fol] = it->imag();

		fol += 1;
	}

	boost::system_time now = boost::get_system_time();
	boost::posix_time::time_duration timelimit = now - limtimeG;
	last_update_samps += received_samples;
	boost::posix_time::time_duration update_diff = now - last_update;
	if (update_diff.ticks() > boost::posix_time::time_duration::ticks_per_second()) {
		double t = (double)update_diff.ticks() / (double)boost::posix_time::time_duration::ticks_per_second();
		double r = (double)last_update_samps / t;
#ifdef CONDEBUG
		std::cout << boost::format("\t%f Msps") % (r / 1e6) << std::endl;
#endif
		last_update_samps = 0;
		last_update = now;
	}


	ticks_diff = now - start;

	// TYPE ERROR BELOW ?
	if ((double)timelimit.ticks() / (double)boost::posix_time::time_duration::ticks_per_second() >= (double)time_requested)stopsignal = true;
	//std::cout << "Time : " << (double)timelimit.ticks() / (double)boost::posix_time::time_duration::ticks_per_second() << std::endl;
	return received_samples;
}
extern "C" __declspec(dllexport) void USRPStopStream(void)
{
	uhd::stream_cmd_t cmdarg = uhd::stream_cmd_t::STREAM_MODE_STOP_CONTINUOUS;
	rxstreamG->issue_stream_cmd(cmdarg);
	delete samplebufferGFL;
	//stopsignal = true;
}
extern "C" __declspec(dllexport) const char* USRPFindDevice(void)
{
	uhd::device_addr_t hint;
	uhd::device_addrs_t usrpaddrs = uhd::device::find(hint);

	//int strpos;
	hint = uhd::combine_device_addrs(usrpaddrs);
	std::string foundstring = hint.to_string();
	/*char* retchar= new char [foundstring.length()];
	strncpy_s(retchar,foundstring.size(),foundstring.c_str(),foundstring.length());*/
	size_t csize = strlen(foundstring.c_str()) + sizeof(char);
	char* retptr = NULL;
	retptr = (char*)::CoTaskMemAlloc(csize);
	strcpy_s(retptr, csize, foundstring.c_str());
	return retptr;
	//strpos = foundstring.find("type");
	//std::cout << retchar << std::endl;
	//std::cout << "I found: " << hint.cast("type0", hint);
}
extern "C" __declspec(dllexport) const char* USRPGetConnectedDeviceInfo(void)
{
	std::string usrpstring;
	usrpstring = usrpG->get_pp_string();

	size_t csize = strlen(usrpstring.c_str()) + sizeof(char);
	char* retptr = NULL;
	retptr = (char*)::CoTaskMemAlloc(csize);
	strcpy_s(retptr, csize, usrpstring.c_str());
	return retptr;
}
extern "C" __declspec(dllexport) bool USRPGetInterrupt(void)
{
	return stopsignal;
}

// Should call after setting the stream
//int USRPGetMaxPack(void)
//{
//	return 0;
//}
void RXTest()
{
	int balon;
	float* Iintake;
	float*	Qintake;
	float*	Xintake;
	float* IintakeO;
	float* QintakeO;
	short* IintakeSH;
	short*	QintakeSH;

	short* IintakeSHO;
	short* QintakeSHO;
	double* IintakeDBL;
	double* QintakeDBL;
	double* IintakeDBLO;
	double* QintakeDBLO;


	double frequency = 1e9;
	double samplef = 2e6;
	int samplesize = 100e3;
	double bandwidth = samplef*0.8;
	double gain = 10.0;
	bool DBLtype = 1;



	IintakeDBL = new double[samplesize];
	QintakeDBL = new double[samplesize];
	IintakeDBLO = new double[samplesize];
	QintakeDBLO = new double[samplesize];
	Xintake = new float[samplesize];

	IintakeSH = new short[samplesize];
	QintakeSH = new short[samplesize];
	IintakeSHO = new short[samplesize];
	QintakeSHO = new short[samplesize];
	Xintake = new float[samplesize];


	Iintake = new float[samplesize];
	Qintake = new float[samplesize];
	IintakeO = new float[samplesize];
	QintakeO = new float[samplesize];



	////balon = FFTUHDPlan("...", " ", "0", "internal", 33e6, 2e6, 1024, 1000, 5.0, 0, Iintake, Qintake, Xintake);
	//balon = FFTUHDPlanP("addr=192.168.10.2", " ", "0", "internal", frequency, samplef, samplesize, bandwidth, gain, 0, Iintake, Qintake, Xintake);
	//std::cout << balon << std::endl;
	//for (int i = 0; i < samplesize; ++i) std::cout << Iintake[i] << " and " << Qintake[i] << " at " << i << std::endl;
	//std::cin >> balon;
	if (USRPConnection("addr=192.168.10.2"))
	{

		// USRP SET DATA FORMAT 
		USRPSetDataFormat(DBLtype);
		USRPSetCLK("internal");
		USRPSetSamplingRate(samplef);
		USRPSetFrequency(frequency);
		USRPSetGain(gain);
		USRPSetBW(bandwidth);
		USRPSetSampleSize(samplesize);
		USRPSetAntenna("RX-A");
		USRPSetRequestTime(4);
		USRPSetRXStream(true);
	}
	else std::cout << "USRP NOT FOUND, CHECK CONNECTIONS AND ADDRESS" << std::endl;
	//std::cout << "Max Size: " << USRPGetMaxPack() << std::endl;

	int packetsize = 0;
	int recsamp = 0;
	double varfrequency = frequency;

	while ((recsamp < samplesize || contRXG) && !stopsignal)
	{
		if (packetsize == 1)
		{
			if (DBLtype == 3)
			{
				memcpy(IintakeDBLO, IintakeDBL, sizeof(double)*samplesize);
				memcpy(QintakeDBLO, QintakeDBL, sizeof(double)*samplesize);
			}
			else if (DBLtype == 2)
			{
				memcpy(IintakeO, Iintake, sizeof(float)*samplesize);
				memcpy(QintakeO, Qintake, sizeof(float)*samplesize);
			}
			else if (DBLtype == 1)
			{
				memcpy(IintakeSHO, IintakeSH, sizeof(short)*samplesize);
				memcpy(QintakeSHO, QintakeSH, sizeof(short)*samplesize);
			}

			//IintakeO = Iintake;
			//QintakeO = Qintake;
		}
		if (DBLtype == 3)
		{
			recsamp += USRPStartRXDBL(IintakeDBL, QintakeDBL);
		}
		else if (DBLtype == 2)
		{
			recsamp += USRPStartRX(Iintake, Qintake);
		}
		else if (DBLtype == 1)
		{
			recsamp += USRPStartRXSH(IintakeSH, QintakeSH);
		}


		packetsize += 1;
		std::cout << "AQ Samples: " << recsamp << " Packet ID: " << packetsize << std::endl;
		std::signal(SIGINT, &sig_int_handler);
	}
	double t = (double)ticks_diff.ticks() / (double)boost::posix_time::time_duration::ticks_per_second();
	std::cout << boost::format("Received %d samples in %f seconds") % recsamp % t << std::endl;
	double r = (double)recsamp / t;
	std::cout << boost::format("%f Msps") % ((r / 1e6) / packetsize) << std::endl;
	USRPStopStream();

	int Ifamiliarity = 0;
	int Qfamiliarity = 0;
	std::ofstream ofile("IandQ.txt");
	if (DBLtype == 3)
	{
		for (int i = 0; i < samplesize; ++i)
		{
			if (IintakeDBL[i] == IintakeDBLO[i])Ifamiliarity += 1;
			if (QintakeDBL[i] == QintakeDBLO[i])Qfamiliarity += 1;
			ofile << IintakeDBL[i] << "\t" << QintakeDBL[i] << std::endl;
			//std::cout << Iintake[i] << " and " << Qintake[i] << " at " << i << std::endl;
		}

	}
	else if (DBLtype == 2)
	{
		for (int i = 0; i < samplesize; ++i)
		{
			if (Iintake[i] == IintakeO[i])Ifamiliarity += 1;
			if (Qintake[i] == QintakeO[i])Qfamiliarity += 1;
			ofile << Iintake[i] << "\t" << Qintake[i] << std::endl;
			//std::cout << Iintake[i] << " and " << Qintake[i] << " at " << i << std::endl;
		}
	}
	else if (DBLtype == 1)
	{
		for (int i = 0; i < samplesize; ++i)
		{
			if (IintakeSH[i] == IintakeSHO[i])Ifamiliarity += 1;
			if (QintakeSH[i] == QintakeSHO[i])Qfamiliarity += 1;
			ofile << IintakeSH[i] << "\t" << QintakeSH[i] << std::endl;
			//std::cout << Iintake[i] << " and " << Qintake[i] << " at " << i << std::endl;
		}
	}

	ofile.close();
	std::cout << "I Familiarity: " << Ifamiliarity << " Q Familiarity: " << Qfamiliarity << std::endl;
	std::cin >> balon;
}
void TXTest()
{
	double frequency = 1e9;
	double samplef = 2e6;
	int samplesize = 100e3;
	double bandwidth = samplef*0.8;
	double gain = 10.0;
	bool DBLtype = 1;
	const char* filename = "data.dat";
	if (USRPConnection("addr=192.168.10.2"))
	{

		// USRP SET DATA FORMAT 
		USRPSetDataFormat(DBLtype);
		USRPSetCLK("internal");
		USRPSetTxRate(samplef);
		USRPSetTxFrequency(frequency);
		USRPSetTxGain(gain);
		USRPSetTxBW(bandwidth);
		USRPSetSampleSize(samplesize);
		USRPSetAntenna("RX-A");
		USRPSetTXStream();
		USRPStartTXFile(filename);

	}
}
int main()
{


	return 0;
}

