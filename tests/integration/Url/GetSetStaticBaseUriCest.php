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

namespace Phalcon\Test\Integration\Url;

use IntegrationTester;
use Phalcon\Url;

class GetSetStaticBaseUriCest
{
    /**
     * Tests Phalcon\Url :: getStaticBaseUri()/setStaticBaseUri()
     *
     * @author Phalcon Team <team@phalconphp.com>
     * @since  2018-11-13
     */
    public function urlGetSetStaticBaseUri(IntegrationTester $I)
    {
        $I->wantToTest('Url - getStaticBaseUri()/setStaticBaseUri()');

        $url = new Url();

        $path = 'https://phalconphp.com';

        $url->setStaticBaseUri($path);

        $I->assertEquals(
            $path,
            $url->getStaticBaseUri()
        );
    }

    /**
     * Tests Phalcon\Url :: getStaticBaseUri()/setStaticBaseUri() -
     * getBaseUrl()
     *
     * @author Phalcon Team <team@phalconphp.com>
     * @since  2018-11-13
     */
    public function urlGetSetStaticBaseUriGetBaseUri(IntegrationTester $I)
    {
        $I->wantToTest('Url - getStaticBaseUri()/setStaticBaseUri() - getBaseUri()');

        $url = new Url();

        $expected = 'https://phalconphp.com';

        $url->setBaseUri($expected);

        $actual = $url->getStaticBaseUri();

        $I->assertEquals($expected, $actual);
    }
}
