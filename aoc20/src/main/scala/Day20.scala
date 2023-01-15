import scala.annotation.tailrec
import scala.collection.mutable.ArrayBuffer
import scala.io.Source
import scala.util.control.NonLocalReturns

object Day20:

  type Border = Vector[String]
  private val SZ = 12
  private val UP = 0
  private val RIGHT = 1
  private val DOWN = 2
  private val LEFT = 3
  private val MONSTER = Vector(
    "                  # ",
    "#    ##    ##    ###",
    " #  #  #  #  #  #   "
  )

  private def parseTile(lines: Vector[String]): (Long, Border, Vector[String]) =
    val id = lines(0).replaceAll("\\D", "").toLong
    val left = lines.slice(1, 11).map(_.head).mkString
    val right = lines.slice(1, 11).map(_.last).mkString
    val content = lines.slice(2, 10).map(line => line.substring(1, 9))
    (id, Vector(lines(1), right, lines(10), left), content)

  private def rotate(t: Border): Border =
    Vector(t(LEFT).reverse, t(UP), t(RIGHT).reverse, t(DOWN))

  private def flip(t: Border): Border =
    Vector(t(UP).reverse, t(LEFT), t(DOWN).reverse, t(RIGHT))

  private def ok(i: Int, newBorders: Border, arr: ArrayBuffer[(Int, Int, Border)]): Boolean =
    if i % SZ > 0 then
      if !arr(i - 1)._3(RIGHT).equals(newBorders(LEFT)) then return false
    if i >= SZ then
      if !arr(i - SZ)._3(DOWN).equals(newBorders(UP)) then return false
    true

  private def tryit(i: Int, borders: Vector[Border], arr: ArrayBuffer[(Int, Int, Border)],
                    used: ArrayBuffer[Boolean]): Boolean =
    if i == SZ * SZ then true
    else
      borders.indices.foreach(j => {
        if !used(j) then
          var newBorders = borders(j)
          (0 until 8).foreach(k => {
            if i == 0 || ok(i, newBorders, arr) then
              arr(i) = (j, k, newBorders)
              used(j) = true
              if tryit(i + 1, borders, arr, used) then return true
              used(j) = false
            newBorders = rotate(newBorders)
            if k == 3 then newBorders = flip(newBorders)
          })
      })
      false

  @tailrec
  private def rotatePic(pic: Vector[String], step: Int): Vector[String] =
    if step == 0 then pic
    else
      val rotateOnce = pic(0).indices.map(i => {
        pic.map(_(i)).mkString.reverse
      }).toVector
      rotatePic(rotateOnce, step - 1)

  private def flipPic(pic: Vector[String]): Vector[String] =
    pic.map(_.reverse)

  private def getPic(pic: Vector[String], dir: Int): Vector[String] =
    if dir < 4 then rotatePic(pic, dir)
    else rotatePic(flipPic(pic), dir - 4)

  private def buildPic(contents: Vector[Vector[String]], arr: ArrayBuffer[(Int, Int, Border)]): Vector[ArrayBuffer[Char]] =
    val directedPics = arr.map((i, j, _) => getPic(contents(i), j))
    Vector.tabulate(SZ * 8)(i => {
      ArrayBuffer.tabulate(SZ * 8)(j => {
        directedPics((i / 8) * SZ + j / 8)(i % 8)(j % 8)
      })
    })

  private def checkMonster(i: Int, j: Int, pic: Vector[ArrayBuffer[Char]], monster: Vector[String]): Unit =
    monster.indices.foreach(u => {
      monster(u).indices.foreach(v => {
        if monster(u)(v) == '#' && pic(i + u)(j + v) == '.' then return
      })
    })
    monster.indices.foreach(u => {
      monster(u).indices.foreach(v => {
        if monster(u)(v) == '#' then pic(i + u)(j + v) = 'O'
      })
    })

  private def findMonster(pic: Vector[ArrayBuffer[Char]], monster: Vector[String]): Unit =
    (0 until 4).foreach(r => {
      val rotatedMonster = rotatePic(monster, r)
      for
        i <- 0 until pic.length - rotatedMonster.length
        j <- 0 until pic.length - rotatedMonster(0).length
      do checkMonster(i, j, pic, rotatedMonster)
    })

  def main(args: Array[String]): Unit =
    val lines = Source.fromResource("day20.txt").getLines().toVector
    val (ids, borders, contents) = lines.grouped(12).map(parseTile).toVector.unzip3
    val arr: ArrayBuffer[(Int, Int, Border)] = ArrayBuffer.fill(SZ * SZ)((-1, -1, Vector.empty))
    tryit(0, borders, arr, ArrayBuffer.fill(SZ * SZ)(false))
    println(ids(arr.head._1) * ids(arr(SZ - 1)._1) * ids(arr(SZ * (SZ - 1))._1) * ids(arr.last._1))

    val fullPic = buildPic(contents, arr)
    findMonster(fullPic, MONSTER)
    findMonster(fullPic, flipPic(MONSTER))
    println(fullPic.flatten.count(_ == '#'))