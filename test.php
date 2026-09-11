<?php

trait Authenticated
{
    public function auth(string $name): bool
    {
        if (empty(trim($name))) {
            return false;
        }
        return true;
    }
}

trait LoggedIn
{
    public function log_status(string $name): bool
    {
        if (empty(trim($name))) {
            return false;
        }
        return true;
    }
}

class UserSession
{
    use Authenticated, LoggedIn;
    public string $name;
    public function __construct(string $name)
    {
        $this->name = $name;
    }

    public function checkUserStatus(): void
    {
        $isAuth = $this->auth($this->name);
        $isLogged = $this->log_status($this->name);

        if ($isLogged && $isAuth) {
            echo "User '{$this->name} is active and authenticated. \n'";
        } else {
            echo "User '{$this->name} is an invalid Entry'";
        }
    }
}

$validateUser = new UserSession("Sarthak");
$validateUser->checkUserStatus();

$invalidateUser = new UserSession(" ");
$invalidateUser->checkUserStatus();

?>
