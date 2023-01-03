import scala.annotation.tailrec
import scala.io.Source

object Day11:

  private val dir = Vector((-1, -1), (-1, 0), (-1, 1), (0, -1), (0, 1), (1, -1), (1, 0), (1, 1))
  private val part1 = false
  private val tolerance = if part1 then 4 else 5

  @tailrec
  private def checkDir(i: Int, j: Int, lines: Vector[String], dx: Int, dy: Int, step: Int): Boolean =
    val i2 = i + step * dx
    val j2 = j + step * dy
    if i2 >= 0 && i2 < lines.length && j2 >= 0 && j2 < lines(i2).length then
      if lines(i2)(j2) == '#' then true
      else if lines(i2)(j2) == 'L' then false
      else !part1 && checkDir(i, j, lines, dx, dy, step + 1)
    else false

  private def cntOccupied(lines: Vector[String]): Vector[Vector[Int]] =
    lines.indices.map(i => {
      lines(i).indices.map(j => {
        dir.count((dx, dy) => checkDir(i, j, lines, dx, dy, 1))
      }).toVector
    }).toVector

  private def transform(lines: Vector[String]): Vector[String] =
    val cnt = cntOccupied(lines)
    lines.zip(cnt).map((line, cntLine) => {
      line.zip(cntLine).map((char, cnt) => {
        (char, cnt) match
          case ('L', 0) => '#'
          case ('#', c) if c >= tolerance => 'L'
          case _ => char
      }).mkString("")
    })

  @tailrec
  def doit(lines: Vector[String]): Vector[String] =
    val newLines = transform(lines)
    if lines.zip(newLines).forall(_.equals(_)) then lines
    else doit(newLines)

  def main(args: Array[String]): Unit =
    val lines = Source.fromResource("day11.txt").getLines().toVector
    println(doit(lines).mkString("").count(_ == '#'))