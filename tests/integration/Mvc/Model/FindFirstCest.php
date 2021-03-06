<?php
declare(strict_types=1);

/**
 * This file is part of the Phalcon Framework.
 *
 * (c) Phalcon Team <team@phalconphp.com>
 *
 * For the full copyright and license information, please view the LICENSE.txt
 * file that was distributed with this source code.
 */

namespace Phalcon\Test\Integration\Mvc\Model;

use IntegrationTester;
use Phalcon\Mvc\Model\Exception;
use Phalcon\Test\Fixtures\Traits\DiTrait;
use Phalcon\Test\Models\Customers;
use Phalcon\Test\Models\Robots;
use Phalcon\Test\Models\RobotsExtended;

/**
 * Class FindFirstCest
 */
class FindFirstCest
{
    use DiTrait;

    /**
     * Tests Phalcon\Mvc\Model :: findFirst()
     *
     * @author Phalcon Team <team@phalconphp.com>
     * @since  2018-11-13
     */
    public function mvcModelFindFirst(IntegrationTester $I)
    {
        $I->wantToTest('Mvc\Model - findFirst()');
        $this->setNewFactoryDefault();
        $this->setDiMysql();

        $robot = Robots::findFirst();
        $class = Robots::class;
        $I->assertInstanceOf($class, $robot);
        $I->assertEquals(1, $robot->id);

        $robot = Robots::findFirst(null);
        $class = Robots::class;
        $I->assertInstanceOf($class, $robot);

        $robot = Robots::findFirst(1);
        $class = Robots::class;
        $I->assertInstanceOf($class, $robot);
    }

    /**
     * Tests Phalcon\Mvc\Model :: findFirst() - not found
     *
     * @author Phalcon Team <team@phalconphp.com>
     * @since  2018-11-13
     */
    public function mvcModelFindFirstNotFound(IntegrationTester $I)
    {
        $I->wantToTest('Mvc\Model - findFirst() - not found');
        $this->setNewFactoryDefault();
        $this->setDiMysql();

        $robot = Robots::findFirst(
            [
                'conditions' => 'id < 0',
            ]
        );
        $I->assertNull($robot);
    }

    /**
     * Tests Phalcon\Mvc\Model :: findFirstBy() - not found
     *
     * @author Phalcon Team <team@phalconphp.com>
     * @since  2018-11-13
     */
    public function mvcModelFindFirstByNotFound(IntegrationTester $I)
    {
        $I->wantToTest('Mvc\Model - findFirstBy() - not found');
        $this->setNewFactoryDefault();
        $this->setDiMysql();

        $robot = Customers::findFirstByEmail('unknown');
        $I->assertNull($robot);
    }

    /**
     * Tests Phalcon\Mvc\Model :: findFirst() - extended
     *
     * @author Phalcon Team <team@phalconphp.com>
     * @since  2018-11-13
     */
    public function mvcModelFindFirstExtended(IntegrationTester $I)
    {
        $I->wantToTest('Mvc\Model - findFirst() - extended');
        $this->setNewFactoryDefault();
        $this->setDiMysql();

        $robot = RobotsExtended::findFirst(1);
        $class = RobotsExtended::class;
        $I->assertInstanceOf($class, $robot);
        $I->assertEquals(1, $robot->id);

        $robot = RobotsExtended::findFirst(0);
        $I->assertNull($robot);
    }

    /**
     * Tests Phalcon\Mvc\Model :: findFirst() - exception
     *
     * @author Phalcon Team <team@phalconphp.com>
     * @since  2018-11-13
     */
    public function mvcModelFindFirstException(IntegrationTester $I)
    {
        $I->wantToTest('Mvc\Model - findFirst() - exception');
        $this->setNewFactoryDefault();
        $this->setDiMysql();

        $I->expectThrowable(
            new Exception('Parameters passed must be of type array, string, numeric or null'),
            function () {
                Robots::findFirst(false);
            }
        );
    }
}
