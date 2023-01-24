import scala.annotation.tailrec
import scala.io.Source

object Day24:

  @tailrec
  def move(x: Int, y: Int, steps: String): (Int, Int) =
    if steps.equals("") then (x, y)
    else if steps.startsWith("e") then move(x + 1, y, steps.substring(1))
    else if steps.startsWith("w") then move(x - 1, y, steps.substring(1))
    else
      steps.substring(0, 2) match
        case "se" => move(x + (y % 2).abs, y - 1, steps.substring(2))
        case "sw" => move(x - 1 + (y % 2).abs, y - 1, steps.substring(2))
        case "ne" => move(x + (y % 2).abs, y + 1, steps.substring(2))
        case "nw" => move(x - 1 + (y % 2).abs, y + 1, steps.substring(2))

  private def getNeighbors(x: Int, y: Int): List[(Int, Int)] =
    List((x - 1, y), (x + 1, y), (x + (y % 2).abs, y - 1), (x - 1 + (y % 2).abs, y - 1),
      (x + (y % 2).abs, y + 1), (x - 1 + (y % 2).abs, y + 1))

  @tailrec
  def update(blackTiles: Set[(Int, Int)], steps: Int): Set[(Int, Int)] =
    if steps == 0 then blackTiles
    else
      val (bx, by) = blackTiles.unzip(identity)
      val newBlacks = for
        x <- bx.min - 1 to bx.max + 1
        y <- by.min - 1 to by.max + 1
        cntBlack = getNeighbors(x, y).count((x2, y2) => blackTiles.contains((x2, y2)))
        if (blackTiles.contains((x, y)) && cntBlack != 0 && cntBlack <= 2)
          || (!blackTiles.contains((x, y)) && cntBlack == 2)
      yield (x, y)
      update(newBlacks.toSet, steps - 1)

  def main(args: Array[String]): Unit =
    val lines = Source.fromResource("day24.txt").getLines()
    val flippedTiles: Set[(Int, Int)] = lines.foldRight(Set.empty)((line, flippedTiles) => {
      val pos = move(0, 0, line)
      if flippedTiles.contains(pos) then flippedTiles - pos
      else flippedTiles + pos
    })
    println(flippedTiles.size)
    println(update(flippedTiles, 100).size)