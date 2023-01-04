import scala.annotation.tailrec
import scala.collection.mutable.ArrayBuffer
import scala.io.Source

object Day13:

  private def powmod(a: Long, n: Long, p: Long): Long =
    if n == 0 then 1L
    else
      val tmp = powmod(a, n / 2, p)
      val res = (tmp * tmp) % p
      if n % 2 == 1 then (res * a) % p
      else res

  def main(args: Array[String]): Unit =
    val lines = Source.fromResource("day13.txt").getLines().toVector
    val t = lines(0).toInt
    val nums = lines(1).split(",").zipWithIndex
      .filter((num, _) => !num.equals("x"))
      .map((num, pos) => (num.toLong, pos)).toVector
    val (t1, bus) = nums.map((p, _) => (((t + p - 1) / p) * p, p)).min
    println((t1 - t) * bus)

    val x = ArrayBuffer.fill(nums.length)(0L)
    var res = 0L
    var prod = 1L
    nums.indices.foreach(i => {
      val (p, a) = nums(i)
      x(i) = (p - a % p) % p
      (0 until i).foreach(j => {
        val r = powmod(nums(j)._1, p - 2, p)
        x(i) = (((x(i) - x(j) % p + p) % p) * r) % p
      })
      res = res + prod * x(i)
      prod = prod * p
    })

    println(res)