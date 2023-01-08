import scala.annotation.tailrec
import scala.collection.mutable
import scala.collection.mutable.ArrayBuffer
import scala.io.Source

object Day17:

  private def cntActiveNeighbors(x: Int, y: Int, z: Int, t: Int, active: Set[(Int, Int, Int, Int)]): Int =
    val res = for
      dx <- -1 to 1
      dy <- -1 to 1
      dz <- -1 to 1
      dt <- -1 to 1
      if dx != 0 || dy != 0 || dz != 0 || dt != 0
      if active.contains((x + dx, y + dy, z + dz, t + dt))
    yield 1
    res.length

  def transform(active: Set[(Int, Int, Int, Int)]): Set[(Int, Int, Int, Int)] =
    val maxx = active.map((x, _, _, _) => x).max
    val minx = active.map((x, _, _, _) => x).min
    val maxy = active.map((_, y, _, _) => y).max
    val miny = active.map((_, y, _, _) => y).min
    val maxz = active.map((_, _, z, _) => z).max
    val minz = active.map((_, _, z, _) => z).min
    val maxt = active.map((_, _, _, t) => t).max
    val mint = active.map((_, _, _, t) => t).min
    val res = for
      x <- minx - 1 to maxx + 1
      y <- miny - 1 to maxy + 1
      z <- minz - 1 to maxz + 1
      t <- mint - 1 to maxt + 1
      cnt = cntActiveNeighbors(x, y, z, t, active)
      if (active.contains((x, y, z, t)) && (cnt == 2 || cnt == 3)) || (!active.contains((x, y, z, t)) && cnt == 3)
    yield (x, y, z, t)
    res.toSet

  def main(args: Array[String]): Unit =
    val lines = Source.fromResource("day17.txt").getLines().toVector
    val active = lines.indices.flatMap(i => lines(i).indices.filter(lines(i)(_) == '#').map((i, _, 0, 0)))
      .toSet
    val res = (1 to 6).foldLeft(active)((active, _) => transform(active))
    println(res.size)