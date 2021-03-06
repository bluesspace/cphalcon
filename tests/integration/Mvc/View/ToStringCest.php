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

namespace Phalcon\Test\Integration\Mvc\View;

use function dataDir;
use IntegrationTester;
use Phalcon\Di;
use Phalcon\Helper\Str;
use Phalcon\Mvc\View;

/**
 * Class ToStringCest
 */
class ToStringCest
{
    /**
     * Tests Phalcon\Mvc\View :: toString()
     *
     * @author Phalcon Team <team@phalconphp.com>
     * @since  2018-11-13
     */
    public function mvcViewToString(IntegrationTester $I)
    {
        $I->wantToTest('Mvc\View - toString()');

        $container = new Di();
        $view = new View();
        $view->setViewsDir(Str::dirSeparator(dataDir('fixtures/views')));

        $view->setDI($container);

        $expected = 'lolphalcon';
        $actual   = $view->toString(
            'currentrender',
            'query',
            [
                'name' => 'phalcon',
            ]
        );
        $I->assertEquals($expected, $actual);
    }
}
