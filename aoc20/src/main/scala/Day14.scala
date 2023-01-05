import scala.io.Source
import scala.collection.mutable

object Day14:

  private def process(state: (Long, Long, Vector[Long]), line: String): (Long, Long, Vector[Long]) =
    val (mask0, mask1, mem) = state
    if line.startsWith("mask") then
      val mask = line.split(" ")(2)
      val newMask0 = java.lang.Long.parseLong(mask.replace('X', '1'), 2)
      val newMask1 = java.lang.Long.parseLong(mask.replace('X', '0'), 2)
      (newMask0, newMask1, mem)
    else
      val tokens = line.split("[\\[\\] ]")
      val pos = tokens(1).toInt
      val value = tokens(4).toLong
      (mask0, mask1, mem.updated(pos, (value & mask0) | mask1))

  private def process2(state: (Long, Long), line: String, mem: mutable.Map[Long, Long]): (Long, Long) =
    val (mask1, maskx) = state
    if line.startsWith("mask") then
      val mask = line.split(" ")(2)
      val newMask1 = java.lang.Long.parseLong(mask.replace('X', '0'), 2)
      val newMaskx = java.lang.Long.parseLong(mask.replace('1', '0')
        .replace('X', '1'), 2)
      (newMask1, newMaskx)
    else
      val tokens = line.split("[\\[\\] ]")
      val pos = tokens(1).toInt | mask1
      val value = tokens(4).toLong
      mem(pos) = value
      var xor_mask = maskx
      while xor_mask > 0 do
        mem(pos ^ xor_mask) = value
        xor_mask = (xor_mask - 1L) & maskx
      (mask1, maskx)

  def main(args: Array[String]): Unit =
    val lines = Source.fromResource("day14.txt").getLines().toVector
    val (_, _, mem) = lines.foldLeft((0L, 0L, Vector.fill(65536)(0L)))(process)
    println(mem.sum)

    val mem2: mutable.Map[Long, Long] = mutable.Map.empty
    lines.foldLeft((0L, 0L))((state, line) => process2(state, line, mem2))
    println(mem2.values.sum)