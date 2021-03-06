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

namespace Phalcon\Test\Unit\Cache\Adapter\Memory;

use Phalcon\Cache\Adapter\Memory;
use Phalcon\Storage\SerializerFactory;
use UnitTester;

class DeleteCest
{
    /**
     * Tests Phalcon\Cache\Adapter\Memory :: delete()
     *
     * @author Phalcon Team <team@phalconphp.com>
     * @since  2019-03-31
     */
    public function cacheAdapterMemoryDelete(UnitTester $I)
    {
        $I->wantToTest('Cache\Adapter\Memory - delete()');

        $serializer = new SerializerFactory();
        $adapter    = new Memory($serializer);

        $key = 'cache-data';

        $adapter->set($key, 'test');

        $I->assertTrue(
            $adapter->has($key)
        );

        $I->assertTrue(
            $adapter->delete($key)
        );

        $I->assertFalse(
            $adapter->has($key)
        );
    }

    /**
     * Tests Phalcon\Cache\Adapter\Memory :: delete() - twice
     *
     * @author Phalcon Team <team@phalconphp.com>
     * @since  2019-03-31
     */
    public function cacheAdapterMemoryDeleteTwice(UnitTester $I)
    {
        $I->wantToTest('Cache\Adapter\Memory - delete() - twice');

        $serializer = new SerializerFactory();
        $adapter    = new Memory($serializer);

        $key = 'cache-data';

        $adapter->set($key, 'test');

        $I->assertTrue(
            $adapter->has($key)
        );

        $I->assertTrue(
            $adapter->delete($key)
        );

        $I->assertFalse(
            $adapter->delete($key)
        );
    }

    /**
     * Tests Phalcon\Cache\Adapter\Memory :: delete() - unknown
     *
     * @author Phalcon Team <team@phalconphp.com>
     * @since  2019-03-31
     */
    public function cacheAdapterMemoryDeleteUnknown(UnitTester $I)
    {
        $I->wantToTest('Cache\Adapter\Memory - delete() - unknown');

        $serializer = new SerializerFactory();
        $adapter    = new Memory($serializer);

        $key = 'cache-data';

        $I->assertFalse(
            $adapter->delete($key)
        );
    }
}
