#include <chrono>
#include <boost/asio.hpp>
#include <libdevcore/FixedHash.h>
#include <libdevcore/Worker.h>
#include <libethcore/Farm.h>
#include <libethcore/EthashAux.h>
#include <libethcore/Miner.h>

#include "BuildInfo.h"


using namespace std;
using namespace boost::asio;
using boost::asio::ip::tcp;
using namespace dev;
using namespace dev::eth;

// Json::Value is not part of the public interface 
namespace Json {
class Value;
}

class EthStratumClientV2 : public Worker
{
public:
	EthStratumClientV2(GenericFarm<EthashProofOfWork> * f, MinerType m, string const & host, string const & port, string const & user, string const & pass, int const & retries, int const & protocol, string const & email);
	~EthStratumClientV2();

	void setFailover(string const & host, string const & port);
	void setFailover(string const & host, string const & port, string const & user, string const & pass);

	bool isRunning() { return m_running; }
	bool isConnected() { return m_connected; }
	h256 currentHeaderHash() { return m_current.headerHash; }
	bool current() { return m_current; }
	unsigned waitState() { return m_waitState; }
	bool submit(EthashProofOfWork::Solution solution);
	void reconnect();
private:
	void workLoop() override;
	void connect();
	
	void disconnect();

	void processReponse(Json::Value& responseObject);
	
	MinerType m_minerType;

	cred_t * p_active;
	cred_t m_primary;
	cred_t m_failover;

	string m_worker; // eth-proxy only;

	bool m_connected;
	bool m_running = true;

	int	m_retries = 0;
	int	m_maxRetries;
	unsigned int m_sharesPending = 0;
	std::chrono::steady_clock::time_point m_shareTimer;

	int m_waitState = MINER_WAIT_STATE_WORK;

	string m_response;

	GenericFarm<EthashProofOfWork> * p_farm;
	EthashProofOfWork::WorkPackage m_current;
	EthashProofOfWork::WorkPackage m_previous;

	string m_job;
	string m_previousJob;
	EthashAux::FullType m_dag;

	boost::asio::io_service m_io_service;
	tcp::socket m_socket;

	boost::asio::streambuf m_requestBuffer;
	boost::asio::streambuf m_responseBuffer;

	int m_protocol;
	string m_email;

	double m_nextWorkDifficulty;

	h64 m_extraNonce;
	int m_extraNonceHexSize;

	void processExtranonce(std::string& enonce);
	void jobReport();
};
