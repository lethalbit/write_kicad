// SPDX-License-Identifier: BSD-3-Clause

#include <algorithm>
#include <unordered_map>
#include <vector>
#include <sstream>
#include <iterator>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wsign-conversion"
#pragma GCC diagnostic ignored "-Warith-conversion"
#pragma GCC diagnostic ignored "-Wconversion"
#pragma GCC diagnostic ignored "-Wcast-qual"
#pragma GCC diagnostic ignored "-Wformat"
#pragma GCC diagnostic ignored "-Wdouble-promotion"
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#include "kernel/rtlil.h"
#include "kernel/register.h"
#include "kernel/sigtools.h"
#include "kernel/celltypes.h"
#include "kernel/log.h"
#pragma GCC diagnostic pop

#include "config.hh"

namespace cfg = write_kicad::config;

USING_YOSYS_NAMESPACE
PRIVATE_NAMESPACE_BEGIN

struct KiCadBackend : public Backend {
	KiCadBackend() : Backend("kicad", "generate KiCad design files") { }

	void help() override {
		//   |---v---|---v---|---v---|---v---|---v---|---v---|---v---|---v---|---v---|---v---|
		log("\n");
		log("	write_kicad [options]\n");
		log("\n");
		log("This command writes out the selected netlist into a KiCad eeschema schematic file.\n");
		log("\n");
		log("	-split-bus\n");
		log("		Don't combine busses into eescchema busses, but route as individual nets \n");
		log("\n");
		log("about write_kicad:\n");
		log("	license: BSD-3-Clause\n");
		log("	website: https://github.com/lethalbit/write_kicad\n");
		log("	version: %s\n", cfg::version.data());
		log("	bug reports: %s", cfg::bugreport_url.data());
		log("\n");
	}

	bool split_bus{false};

	void execute(
		std::ostream *&f, std::string filename, std::vector<std::string> args, RTLIL::Design *design
	) override {
		std::size_t argidx{1};

		for (; argidx < args.size(); ++argidx) {
			if (args[argidx] == "-split-bus") {
				split_bus = false;
				continue;
			}
			break;
		}

		extra_args(f, filename, args, argidx);
	}

} KiCadBackend;

PRIVATE_NAMESPACE_END
