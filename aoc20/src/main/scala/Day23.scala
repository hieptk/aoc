import scala.annotation.tailrec

object Day23:

  private class Node(val value: Int, var next: Node)

  @tailrec
  private def move(cur: Node, steps: Int, value2Pos: Vector[Node], n: Int): Node =
    if steps == 0 then value2Pos(1)
    else
      val next = cur.next
      val next2 = next.next
      val next3 = next2.next
      var dest = if cur.value > 1 then cur.value - 1 else n
      while dest == next.value || dest == next2.value || dest == next3.value do
        dest = if dest > 1 then dest - 1 else n
      val pos = value2Pos(dest)
      cur.next = next3.next
      next3.next = pos.next
      pos.next = next
      move(cur.next, steps - 1, value2Pos, n)

  @tailrec
  private def doPrint(node: Node): Unit =
    if node.value == 1 then
      println()
    else
      print(node.value)
      doPrint(node.next)

  def main(args: Array[String]): Unit =
    val input = "394618527".split("").map(_.toInt).toVector
    val value2Pos: Vector[Node] = Vector.tabulate(input.length + 1)(i => Node(i, null))
    input.indices.foreach(i => value2Pos(input(i)).next = value2Pos(input((i + 1) % input.length)))
    val res = move(value2Pos(input.head), 100, value2Pos, input.length)
    doPrint(res.next)

    val input2 = input ++ Vector.range(10, 1000001)
    val value2Pos2: Vector[Node] = Vector.tabulate(input2.length + 1)(i => Node(i, null))
    input2.indices.foreach(i => value2Pos2(input2(i)).next = value2Pos2(input2((i + 1) % input2.length)))
    val res2 = move(value2Pos2(input2.head), 10000000, value2Pos2, input2.length)
    println(res2.next.value.toLong * res2.next.next.value)