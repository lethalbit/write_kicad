// SPDX-License-Identifier: BSD-3-Clause

#pragma once
#if !defined(DISCRETIZE_BACKEND_GRAPH_HH)
#define DISCRETIZE_BACKEND_GRAPH_HH

#include <string>
#include <cstdint>
#include <cstddef>
#include <tuple>
#include <vector>
#include <algorithm>
#include <type_traits>


namespace write_kicad {

	template <
		typename id_type,
		typename std::enable_if<std::is_integral<id_type>::value, bool>::type = true
	>
	struct graph_t final {
		struct edge_t final {
		private:
			id_type _id;
			std::string _name;
		public:
			edge_t(id_type id, std::string name) noexcept :
				_id{id}, _name{name} { }

			[[nodiscard]]
			const id_type id() const noexcept { return _id; }
			[[nodiscard]]
			const std::string& name() const noexcept { return _name; }
		};
		struct vertex_t final {
		private:
			id_type _id;
			std::string _name;
			std::vector<id_type> _edge_ids{};
			/* (x, y) */
			std::tuple<double, double> _position{0., 0.};

		public:
			vertex_t(id_type id, std::string name) noexcept :
				_id{id}, _name{name} { }

			[[nodiscard]]
			const id_type id() const noexcept { return _id; }
			[[nodiscard]]
			const std::string& name() const noexcept { return _name; }

			[[nodiscard]]
			const std::size_t edge_count() const noexcept { return _edge_ids.size(); }
			void add_edge(const id_type id) noexcept {
				_edge_ids.push_back(id);
			}

			void remove_edge(const id_type id) noexcept {
				std::remove(_edge_ids.begin(), _edge_ids.end(), id);
			}

			void dedupe_edges() noexcept {
				// First sort the edges so duplicate ids are adjacent
				std::sort(_edge_ids.begin(), _edge_ids.end());
				// Then filter out all duplicate adjacent ids
				std::unique(_edge_ids.begin(), _edge_ids.end());
			}

			[[nodiscard]]
			const std::tuple<double, double> position() const noexcept { return _position; }
			[[nodiscard]]
			const double& x() const noexcept { return std::get<0>(_position); }
			[[nodiscard]]
			const double& y() const noexcept { return std::get<1>(_position); }

			void position(const double _x, const double _y) noexcept { x(_x); y(_y); }
			void x(const double x) noexcept { std::get<0>(_position) = x; }
			void y(const double y) noexcept { std::get<1>(_position) = y; }
		};

	private:
		std::vector<vertex_t> _vertices;
		std::vector<edge_t> _edges;
	public:
		constexpr graph_t() noexcept { }

	};


	/* Default graph type using std::uint64_t for IDs */
	using graph = graph_t<std::uint64_t>;

}

#endif /* DISCRETIZE_BACKEND_GRAPH_HH */
