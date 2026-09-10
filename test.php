<?php

interface PaymentGateway
{
    public function paymentType(string $type): int;
}

class BankAccount implements PaymentGateway
{
    private float $balance = 0.0;

    public function __construct(float $initBalance)
    {
        if ($initBalance > 0) {
            $this->balance = $initBalance;
        }
    }

    public function deposit(float $amount): void
    {
        if ($amount > 0) {
            $this->balance = $amount;
        }
    }

    public function getBalance(): float
    {
        return $this->balance;
    }

    #[Override]
    public function paymentType(string $type): int
    {
        if ($type === "card") {
            return 1;
        }
        return 2;
    }
}

class Tower
{
    public function builind(): void
    {
        echo "The house is being build";
    }
}

class Bridge extends Tower
{
    public function isBuilding(): void
    {
        echo "The bridge is being build";
    }
}

$check = new Bridge();
$check->builind();
$check->isBuilding();

interface Shape
{
    public function calculateArea(): float;
}

class Circle implements Shape
{
    public function __construct(private float $radius) {}

    #[Override]
    public function calculateArea(): float
    {
        return pi() * $this->radius ** 2;
    }
}

class Rectangle implements Shape
{
    public function __construct(
        private float $length,
        private float $breadth,
    ) {}

    #[Override]
    public function calculateArea(): float
    {
        return $this->length * $this->breadth;
    }
}

function printArea(Shape $shape): void
{
    echo "Area : " . $shape->calculateArea() . "\n";
}

$circle = new Circle(12);
$rectangle = new Rectangle(10, 12);
printArea($circle);
printArea($rectangle);

abstract class hasNumber
{
    abstract function caller();
}

class Number extends hasNumber
{
    #[Override]
    public function caller()
    {
        echo "Calling from the abstract class. ";
    }
}
$number = new Number();
$number->caller();

?>
