#include "day8_input.hpp"

#include <array>
#include <iostream>
#include <ranges>
#include <string>
#include <vector>

constexpr auto table =
	std::to_array<std::string_view>({"....1.y.D...Y..........w....m.....................",
									 "..R..D..5....Y...1.........w.........G............",
									 "........R........D..o.............................",
									 ".............H......Y...w.....m...................",
									 ".......R..................3.........v.............",
									 "..1...D..5.........o................0.Bm..........",
									 "......5y.....o.........................3..........",
									 "....H...y......Z...............................0..",
									 "..............H.x..............m........w..g......",
									 "..........................A.......................",
									 ".........................................fg.......",
									 "...8.............v.....e............3B.....2......",
									 ".............5.....r......B.......2...........G..0",
									 "......................v....................3g.....",
									 "......P..............Y...c...........M.2.G........",
									 "..................................................",
									 ".....H....Z.............................K.......0.",
									 "....8d..Z......................u....X......f.g....",
									 "......d..P..r..............B.........E.........9..",
									 ".......r...........E..............q...M...........",
									 "...k...............v......Eb........q...........f.",
									 ".....R................b..............U.q9...2.....",
									 ".J......i.............M....q...................K..",
									 "..........d........................M.....A........",
									 ".......Zj..........h................9S............",
									 ".........j..........P..........Q....7.....c.......",
									 ".j........................a.......................",
									 "....j.6.....h.....F..a......L......c.X............",
									 ".................I.......a..b.............A......V",
									 "x........................p..........EK............",
									 ".......6.....................................X....",
									 "..J....................bf.....r.....K.............",
									 ".e..k................................7......X.....",
									 "...x..kP..................u...........U...........",
									 "J.8.....h....d........U....Q........F.c....iC.O...",
									 "...J...h.I..e......................i...7..........",
									 "..............................L.QU.....A......7...",
									 "...............k....t.........a.WO..i.............",
									 ".....4..6..............l...............T..........",
									 "........z...4.....p..........LS...Q...............",
									 "....e..z................t........pS..........C....",
									 "..............I........W.............9..........C.",
									 "..................l..........F...u...O............",
									 "....l............T.t.6...F.........S..s........V..",
									 ".......................t4.........................",
									 ".........z...........................CV....s......",
									 "..z.........IL.......W....p.........V...u.........",
									 ".....................l............................",
									 "........T.......................s.................",
									 "..........T..........4............................"});

constexpr int MAP_SIZE = table.size();
using Nodes = NodesT<MAP_SIZE>;

Point placeDotTwiceAsFar(const Point& P1, const Point& P2, double scale)
{
	return {.x = P1.x + static_cast<int>(scale * (P2.x - P1.x)),
			.y = P1.y + static_cast<int>(scale * (P2.y - P1.y))};
}

bool isPointOnMap(const Point& point, int mapSize)
{
	return (point.x >= 0 && point.x < mapSize) && (point.y >= 0 && point.y < mapSize);
}

void getNodesForAntennas(Nodes& nodes, const Points& antennas, int mapSize)
{
	for(const auto& [p1, p2] : std::views::cartesian_product(antennas, antennas))
	{
		if(p1 == p2) continue;
		auto n1 = placeDotTwiceAsFar(p1, p2, 2.0);
		if(isPointOnMap(n1, mapSize))
		{
			nodes.emplace(std::move(n1));
		}
	}
}

void getNodesForAntennas2(Nodes& nodes, const Points& antennas, int mapSize)
{
	for(const auto& [p1, p2] : std::views::cartesian_product(antennas, antennas))
	{
		if(p1 == p2) continue;
		const Point offset{p2.x - p1.x, p2.y - p1.y};
		Point node{p1.x + offset.x, p1.y + offset.y};
		while(isPointOnMap(node, mapSize))
		{
			nodes.insert(node);
			node = {node.x + offset.x, node.y + offset.y};
		}
	}
}

int main()
{

	const Antennas antennas = parseTable(table);
	drawMap(antennas, std::vector<Point>{}, MAP_SIZE);

	std::cout << "\n\n\n\n";

	Nodes result;
	for(const auto& [type, points] : antennas)
	{
		getNodesForAntennas(result, points, MAP_SIZE);
	}

	std::cout << "Amount of nodes " << result.size() << std::endl;

	Nodes result2;
	for(const auto& [type, points] : antennas)
	{
		getNodesForAntennas2(result2, points, MAP_SIZE);
	}

	std::cout << "Amount of nodes 2 " << result2.size() << std::endl;

	drawMap(antennas, result2, MAP_SIZE);

	return 0;
}