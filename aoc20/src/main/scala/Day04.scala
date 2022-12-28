import scala.io.Source

object Day04:
  private val PART1 = false
  private val EYE_COLORS = Set("amb", "blu", "brn", "gry", "grn", "hzl", "oth")
  private val requiredFields: Map[String, String => Boolean] = Map(
    "byr" -> (_.toIntOption.exists(year => year >= 1920 && year <= 2002)),
    "iyr" -> (_.toIntOption.exists(year => year >= 2010 && year <= 2020)),
    "eyr" -> (_.toIntOption.exists(year => year >= 2020 && year <= 2030)),
    "hgt" -> isValidHeight,
    "hcl" -> "#[0-9a-f]{6}".r.matches,
    "ecl" -> EYE_COLORS.contains,
    "pid" -> "[0-9]{9}".r.matches
  )

  private def isValidHeight(s: String): Boolean =
    if s.endsWith("cm") then
      s.substring(0, s.length - 2).toIntOption.exists(value => value >= 150 && value <= 193)
    else if s.endsWith("in") then
      s.substring(0, s.length - 2).toIntOption.exists(value => value >= 59 && value <= 76)
    else
      false

  private def isValidPassport(passport: String): Boolean =
    val pairs = passport.split("[ \n]")
    val map = Map.from(pairs.map(pair => {
      val tokens = pair.split(":")
      (tokens(0), tokens(1))
    }))
    if !requiredFields.keys.forall(map.contains) then
      return false
    if PART1 then
      return true
    requiredFields.forall((field, validator) => validator(map(field)))

  def main(args: Array[String]): Unit =
    val passports = Source.fromResource("day04.txt").mkString.split("\n\n")
    print(passports.count(isValidPassport))